#include "M_read_handler.h"
#define reader_open(filepath) zircon_reader_open(f, filepath)
#define read_line() zircon_read_line(f)
#define reader_close() zircon_reader_close(f)

#include "cSpec.h"

static void setup_objects_for_tests(void) {
    __init_M_read_handler();
}

void *f;
void setup_file_handler_object(void) {
    f = zircon_new(M_read_handler);
}

module(T_read_handler, {
    before({
        setup_objects_for_tests();
    });

    before_each(&setup_file_handler_object);

    describe("@M_read_handler", {
        it("is a valid object", {
            char *actual = zircon_to_string(f);
            assert_that_charptr(actual equals to "@M_read_handler");
        });
    });

    describe("#reader open", {
        context("on reading an existing file", {
            FILE *fd = fopen("new_file.txt", "w");

            it("reads file: `new_file.txt`", {
                bool actual = reader_open("new_file.txt");
                assert_that(actual is true);
            });
        });

        context("on reading an non existent file return false", {
            it("fails to read a file that is not yet created", {
                bool actual = reader_open("this_filename_does_not_exist");
                assert_that(actual is false);
            });
        });
    });

    describe("#read line", {
        it("reads `123 234 345 456 567 678 789` from `test_file.txt`", {
            FILE *fd = fopen("test_file.txt", "w");
            fprintf(fd, "%s", "123 234 345 456 567 678 789\n");
            fprintf(fd, "%s", "another line");
            fclose(fd);

            reader_open("test_file.txt");
            char *actual = read_line();
            assert_that_charptr(actual equals to "123 234 345 456 567 678 789");
        });
    });

    describe("#reader close", {
        it("opens a file and successfully closes the buffer", {
            reader_open("new_file.txt");

            bool actual = reader_close();
            assert_that(actual is true);
        });
    });

    after({
        remove("new_file.txt");
        remove("test_file.txt");
    });
});

spec_suite({
    T_read_handler();
});

spec({
    run_spec_suite("failing");
});
