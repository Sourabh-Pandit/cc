/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/stdio>
#include <cc/exceptions>
#include <cc/Process>
#include <cc/Process>
#include <cc/FileStatus>
#include <cc/File>
#include <cc/Dir>
#include <cc/DirWalker>
#include "BuildPlan.h"
#include "BuildShell.h"

namespace ccbuild {

BuildShell::BuildShell(const BuildPlan *plan):
    plan_{plan}
{}

String BuildShell::beautify(const String &command) const
{
    if (plan()->options() & BuildPlan::Bootstrap) {
        return command
            ->replace(plan()->sourcePrefix(), String{"$SOURCE"})
            ->replace(Process::getWorkingDirectory(), String{"$PWD"})
            ->replace("$ORIGIN", "'$ORIGIN'");
    }
    return command;
}

bool BuildShell::run(const String &command) const
{
    fout() << beautify(command) << nl;
    if (plan()->options() & BuildPlan::Simulate) return true;
    return Process::execute(command) == 0;
}

Ref<FileStatus> BuildShell::fileStatus(const String &path) const
{
    if (plan()->options() & BuildPlan::Blindfold) return FileStatus::create();
    return FileStatus::readHead(path);
}

void BuildShell::mkdir(const String &path) const
{
    if (!fileStatus(path)->isValid())
        fout("mkdir -p %%\n") << path;
    if (plan()->options() & BuildPlan::Simulate) return;
    Dir::establish(path);
}

void BuildShell::rmdir(const String &path) const
{
    bool exists = fileStatus(path)->isValid();
    if (exists) fout("rmdir %%\n") << path;
    if (plan()->options() & BuildPlan::Simulate) return;
    if (exists) try { Dir::remove(path); } catch (SystemError &) { /*FIXME, directory might not be empty */ }
}

bool BuildShell::clean(const String &path) const
{
    fout("rm -rf %%\n") << path;
    if (plan()->options() & BuildPlan::Simulate) return true;

    if (fileStatus(path)->isValid()) {
        try {
            File::clean(path);
        }
        catch (SystemError &ex) {
            ferr() << ex << nl;
            return false;
        }
    }

    return true;
}

void BuildShell::symlink(const String &path, const String &newPath) const
{
    fout("ln -sf %% %%\n") << path << newPath;
    if (plan()->options() & BuildPlan::Simulate) return;
    try { File::unlink(newPath); } catch (SystemError &) {}
    File::symlink(path, newPath);
}

bool BuildShell::install(const String &sourcePath, const String &destPath) const
{
    String destDirPath = destPath->reducePath();
    bool destDirMissing = destDirPath != "" && !fileStatus(destDirPath)->isValid();
    if (destDirMissing) fout("install -d %%\n") << destDirPath;

    fout("install %% %%\n") << sourcePath << destPath;

    if (plan()->options() & BuildPlan::Simulate) return true;

    try {
        if (destDirMissing) Dir::establish(destDirPath);
        Ref<File> source = File::open(sourcePath);
        Ref<FileStatus> sourceStatus = FileStatus::read(sourcePath);
        Ref<File> sink = File::open(destPath, FileOpen::WriteOnly|FileOpen::Create|FileOpen::Truncate, sourceStatus->mode());
        sink->write(source->map());
    }
    catch (SystemError &ex) {
        fout("%%\n") << ex.message();
        return false;
    }

    return true;
}

bool BuildShell::unlink(const String &path) const
{
    if ((plan()->options() & BuildPlan::Blindfold) || fileStatus(path)->isValid()) {
        if (plan()->options() & BuildPlan::Simulate) {
            fout("rm -f %%\n") << path;
            return true;
        }
        fout("rm %%\n") << path;
        try {
            File::unlink(path);
        }
        catch (SystemError &ex) {
            fout("%%\n") << ex.message();
            return false;
        }
    }
    return true;
}

bool BuildShell::installAll(const String &sourcePrefix, const String &installPrefix) const
{
    Ref<DirWalker> walker = DirWalker::tryOpen(sourcePrefix);
    if (!walker) return true;

    try {
        String sourcePath;
        bool isDir = false;
        while (walker->read(&sourcePath, &isDir)) {
            if (isDir) continue;
            if (
                !install(
                    sourcePath,
                    installPrefix->extendPath(
                        sourcePath->copy(sourcePrefix->count() + 1, sourcePath->count())
                    )
                )
            )
                return false;
        }
    }
    catch (SystemError &ex) {
        fout("%%\n") << ex.message();
        return false;
    }

    return true;
}

bool BuildShell::unlinkAll(const String &sourcePrefix, const String &installPrefix) const
{
    Ref<DirWalker> walker = DirWalker::tryOpen(sourcePrefix);
    if (!walker) return true;

    try {
        String sourcePath;
        bool isDir = false;
        while (walker->read(&sourcePath, &isDir)) {
            if (isDir) continue;
            if (!
                clean(
                    installPrefix->extendPath(
                        sourcePath->copy(sourcePrefix->count() + 1, sourcePath->count())
                    )
                )
            )
                return false;
        }
    }
    catch (SystemError &ex) {
        fout("%%\n") << ex.message();
        return false;
    }

    return true;
}

void BuildShell::cd(const String &path) const
{
    fout("cd %%\n") << path;
    if (plan()->options() & BuildPlan::Simulate) return;
    try { Process::setWorkingDirectory(path); } catch (SystemError &) { /*FIXME*/ }
}

} // namespace ccbuild
