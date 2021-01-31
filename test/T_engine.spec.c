#include "C_engine.h"
#define load_file(filename) zircon_load_file(T_engine_object, filename)
#define aggregate_data() zircon_aggregate_data(T_engine_object)
#define export_file(filename, type) zircon_export_file(T_engine_object, filename, type)

#include "cSpec.h"

static void C_engine_setup_objects(void) {
    __init_C_engine();

    __init_C_loader();
    __init_M_read_handler();

    __init_C_aggregator();
    __init_M_date();
    __init_M_time();
    __init_M_bank_account();

    __init_C_exporter();
    __init_M_write_handler();
}

void *T_engine_object;
void setup_engine_object(void) {
    T_engine_object = zircon_new(C_engine);
}

module(T_engine, {
    before({
        C_engine_setup_objects();
    });

    before_each(&setup_engine_object);
    
    describe("@C_engine", {
        it("is a valid object", {
            char *actual = zircon_to_string(T_engine_object);
            assert_that_charptr(actual equals to "@C_engine");
        });
    });

    describe("#load file", {
        it("is not empty", {
            char *actual = load_file("test.txt");
            nassert_that_charptr(load_file("test.txt") equals to "");
        });

        it("returns the filename passed in", {
            char *actual = load_file("test.txt");
            assert_that_charptr(actual equals to "test.txt");
        });
    });

    describe("#aggregate data", {
        it("is not empty", {
            nassert_that_charptr(aggregate_data() equals to "");
        });

        it("returns the phrase `aggregating data`", {
            assert_that_charptr(aggregate_data() equals to "aggregating data");
        });
    });

    describe("#export file", {
        it("returns an array with the filename and type as elements", {
            char filename[7] = "out.xml";
            char type[4] = "XML";

            void *ex = export_file(filename, type);
            assert_that_charptr(zircon_get_filename(ex) equals to filename);
            assert_that_charptr(zircon_get_type(ex) equals to type);
        });
    });
});
