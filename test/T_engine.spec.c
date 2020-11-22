#include "C_engine.h"
#define load_file(filename) zircon_load_file(e, filename)
#define aggregate_data() zircon_aggregate_data(e)
#define export_file(filename, type) zircon_export_file(e, filename, type)

#include "cSpec.h"
#include "object_setup.zh"

module(T_engine, {
    void *e;
    before({
        setup_objects_for_tests();
        e = zircon_new(C_engine);
    });
    
    describe("@C_engine", {
        it("is a valid object", {
            char *actual = zircon_to_string(e);
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

spec_suite({
    T_engine();
});

spec({
    run_spec_suite("all");
});
