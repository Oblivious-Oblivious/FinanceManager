#include "M_write_handler.h"
#define writer_open(filepath) zircon_writer_open(T_write_handler_object, filepath)
#define write(str) zircon_write(T_write_handler_object, str)
#define write_line(line) zircon_write_line(T_write_handler_object, line)
#define writer_close() zircon_writer_close(T_write_handler_object)

#include "cSpec.h"

static void M_write_handler_setup_objects(void) {
    __init_M_write_handler();
}

void *T_write_handler_object;
void setup_write_handler_object(void) {
    T_write_handler_object = zircon_new(M_write_handler);
}

module(T_write_handler, {
    before({
        M_write_handler_setup_objects();
    });

    before_each(&setup_write_handler_object);

    describe("@M_write_handler", {
        it("is a valid object", {
            char *actual = zircon_to_string(T_write_handler_object);
            assert_that_charptr(actual equals to "@M_write_handler");
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
