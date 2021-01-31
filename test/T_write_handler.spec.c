#include "M_write_handler.h"
#define writer_open(filepath) zircon_writer_open(f, filepath)
#define write(str) zircon_write(f, str)
#define write_line(line) zircon_write_line(f, line)
#define writer_close() zircon_writer_close(f)

#include "cSpec.h"

static void setup_objects_for_tests(void) {
    __init_M_write_handler();
}

void *f;
void setup_file_handler_object(void) {
    f = zircon_new(M_write_handler);
}

module(T_write_handler, {
    before({
        setup_objects_for_tests();
    });

    before_each(&setup_file_handler_object);

    describe("@M_write_handler", {
        it("is a valid object", {
            bool actual = zircon_static_method_is_a(f, "M_write_handler");
            assert_that(true is true);
        });
    });

    describe("#writer open", {
        context("on filename is new", {
            it("opens the file and returns true", {
                bool actual = writer_open("new_file.txt");
                assert_that(actual is true);
            });
        });

        context("on filename already existsing", {
            FILE *fd = fopen("new_file.txt", "w");
            fprintf(fd, "%s", "data in there");
            
            it("deletes the previous file, creates a new one and returns true", {
                /* For ease of use we assume the previous test has passed */
                bool actual = writer_open("new_file.txt");
                assert_that(actual is true);
                /* We expect that the file is now empty */
            });
        });
    });

    describe("#write", {
        it("writes `test data` to input file named `test_write.txt`", {
            writer_open("test_write.txt");
            
            bool actual = write("test data");
            assert_that(actual is true);
        });
    });

    describe("#write line", {
        it("writes `test data` to input file named `test_write_line.txt` with a newline", {
            writer_open("test_write_line.txt");

            bool actual = write_line("test data");
            assert_that(actual is true);
        });
    });

    describe("#writer close", {
        it("opens a file and successfully closes the buffer", {
            writer_open("new_file.txt");

            bool actual = writer_close();
            assert_that(actual is true);
        });
    });

    after({
        remove("new_file.txt");
        remove("test_write.txt");
        remove("test_write_line.txt");
    });
});

spec_suite({
    T_write_handler();
});

spec({
    run_spec_suite("failing");
});
