/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/testing/TestSuite>
#include <cc/debug>
#include <cc/stdio>
#include <cc/File>
#include <cc/Process>

using namespace cc;
using namespace cc::testing;

/** \brief Demonstrate usage of recursive Predicates
  *
  * This test create a small test application which needs an include tree,
  * which is generated prior to the build using Predicates.
  */
class RecursivePredicatesTest: public TestCase
{
    void run()
    {
        class CleanupGuard {
        public:
            CleanupGuard() { clean(); }
            ~CleanupGuard() { clean(); }
            void clean() { File::clean("TestApp"); }
        };
        CleanupGuard cleanupGuard;

        File::save(
            "TestApp/main.cc",
            "#include <testApp/TestClass>\n"
            "int main() { return testApp::TestClass::testMethod(); }\n"
        );

        File::save(
            "TestApp/TestClass.h",
            "#pragma once\n"
            "namespace testApp {\n"
            "class TestClass {\n"
            "public:\n"
            "    static int testMethod();\n"
            "};\n"
            "} // namespace testApp\n"
        );

        File::save(
            "TestApp/TestClass.cc",
            "#include <testApp/TestClass>\n"
            "namespace testApp {\n"
            "int TestClass::testMethod() { return 0; }\n"
            "} // namespace testApp\n"
        );

        File::save(
            "TestApp/Recipe",
            "Application {\n"
            "    name: testApp\n"
            "    Predicate {\n"
            "        target: include/testApp\n"
            "        create: mkdir -p $@\n"
            "        clean: rm -rf $@/..\n"
            "        Predicate {\n"
            "            source: %.h\n"
            "            target: include/testApp/%\n"
            "            update: cp $< $@\n"
            "            remove: rm -rf $@\n"
            "        }\n"
            "    }\n"
            "}\n"
        );

        CC_VERIFY(
            Process::stage("ccbuild jobs=1")
                ->setWorkingDirectory("TestApp")
                ->execute()
            == 0
        );

        /*
        String cwdSaved = Process::getCwd();
        Process::setWorkingDirectory("TestApp");
        CC_VERIFY(Process::execute(cwdSaved + "/ccbuild jobs=1") == 0);
        Process::setWorkingDirectory(cwdSaved);
        CC_VERIFY(File::exists("TestApp/testApp"));*/
    }
};

int main(int argc, char **argv)
{
    CC_TESTSUITE_ADD(RecursivePredicatesTest);

    return TestSuite::instance()->run(argc, argv);
}
