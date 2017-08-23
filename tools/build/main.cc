/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/stdio>
#include <cc/exceptions>
#include <cc/Bundle>
#include "BuildPlan.h"

using namespace ccbuild;

int main(int argc, char **argv)
{
    String toolName = String(argv[0])->fileName();
    int exitCode = 0;
    try {
        exitCode = BuildPlan::create(argc, argv)->run();
    }
    catch (HelpRequest &) {
        fout(
            "Usage: %% [OPTION]... [DIR]\n"
            "Build binaries from source DIR.\n"
            "\n"
            "Options:\n"
            "  -debug          compile-in debug information\n"
            "  -release        release mode (NDEBUG defined)\n"
            "  -static         build static libraries\n"
            "  -verbose        verbose output\n"
            "  -optimize       optimization level / strategy (0, 1, 2, 3, s, g)\n"
            "  -root           file system root for installation (default: \"/\")\n"
            "  -prefix         installation prefix (default: \"/usr\")\n"
            "  -configure      configure the dependencies and show results\n"
            "  -prepare        evaluate predicate rules\n"
            "  -clean          remove all files generated by the build process\n"
            "  -install        install applications, libraries and bundled files\n"
            "  -uninstall      delete installed files\n"
            "  -test           build all tests\n"
            "  -test-run       run all tests until first fails\n"
            "  -test-run-jobs  number of concurrent jobs to spawn for running tests\n"
            "  -test-report    run all tests ($? = number of failed tests)\n"
            "  -test-args      list of arguments to pass to all tests\n"
            "  -compile-flags  custom compile flags\n"
            "  -link-flags     custom link flags\n"
            "  -compiler       select compiler\n"
            "  -jobs           number of concurrent jobs to spawn\n"
            "  -simulate       print build commands without executing them\n"
            "  -blindfold      do not see any existing files\n"
            "  -bootstrap      write bootstrap script\n"
            "  -query          query given properties\n"
            "  -query-all      query all properties\n"
            "  -version        print %% version\n"
        ) << toolName;
    }
    catch (VersionRequest &ex) {
        fout() << "v" << CC_BUNDLE_VERSION << nl;
    }
    catch (UsageError &ex) {
        ferr() << toolName << ": " << ex.message() << nl;
        return 1;
    }
    #ifdef NDEBUG
    catch (Exception &ex) {
        ferr() << toolName << ": " << ex.message() << nl;
        return 1;
    }
    #endif
    return exitCode;
}
