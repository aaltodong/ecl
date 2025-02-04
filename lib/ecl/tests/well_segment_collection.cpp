#include <stdlib.h>
#include <stdbool.h>

#include <ert/util/test_util.hpp>
#include <ert/util/stringlist.hpp>
#include <ert/util/util.h>

#include <ert/ecl/ecl_util.hpp>

#include <ert/ecl_well/well_const.hpp>
#include <ert/ecl_well/well_segment_collection.hpp>

int main(int argc, char **argv) {
    test_install_SIGNALS();

    double *rseg_data = (double *)util_calloc(100, sizeof *rseg_data);
    well_segment_collection_type *sc = well_segment_collection_alloc();
    test_assert_not_NULL(sc);
    test_assert_int_equal(well_segment_collection_get_size(sc), 0);

    {
        int outlet_segment_id = WELL_SEGMENT_OUTLET_END_VALUE;
        int branch_nr = WELL_SEGMENT_BRANCH_INACTIVE_VALUE;
        well_segment_type *ws =
            well_segment_alloc(89, outlet_segment_id, branch_nr, rseg_data);

        well_segment_collection_add(sc, ws);
        test_assert_int_equal(well_segment_collection_get_size(sc), 1);
        test_assert_ptr_equal(well_segment_collection_iget(sc, 0), ws);

        test_assert_false(well_segment_collection_has_segment(sc, 451));
        test_assert_true(well_segment_collection_has_segment(sc, 89));
        test_assert_ptr_equal(well_segment_collection_get(sc, 89), ws);
    }

    {
        int outlet_segment_id = WELL_SEGMENT_OUTLET_END_VALUE;
        int branch_nr = WELL_SEGMENT_BRANCH_INACTIVE_VALUE;
        well_segment_type *ws =
            well_segment_alloc(90, outlet_segment_id, branch_nr, rseg_data);

        well_segment_collection_add(sc, ws);
        test_assert_int_equal(well_segment_collection_get_size(sc), 2);
        test_assert_ptr_equal(well_segment_collection_iget(sc, 1), ws);

        test_assert_false(well_segment_collection_has_segment(sc, 451));
        test_assert_true(well_segment_collection_has_segment(sc, 89));
        test_assert_true(well_segment_collection_has_segment(sc, 90));
        test_assert_ptr_equal(well_segment_collection_get(sc, 90), ws);
        test_assert_NULL(well_segment_collection_get(sc, 76));
    }

    {
        int outlet_segment_id = WELL_SEGMENT_OUTLET_END_VALUE;
        int branch_nr = WELL_SEGMENT_BRANCH_INACTIVE_VALUE;
        well_segment_type *ws =
            well_segment_alloc(89, outlet_segment_id, branch_nr, rseg_data);

        well_segment_collection_add(sc, ws);
        test_assert_int_equal(well_segment_collection_get_size(sc), 2);
        test_assert_ptr_equal(well_segment_collection_iget(sc, 0), ws);

        test_assert_false(well_segment_collection_has_segment(sc, 451));
        test_assert_true(well_segment_collection_has_segment(sc, 89));
        test_assert_ptr_equal(well_segment_collection_get(sc, 89), ws);
    }

    free(rseg_data);
    well_segment_collection_free(sc);

    exit(0);
}
