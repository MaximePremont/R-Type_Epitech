#include "test.h"

/* This input caused uninitialized reads in the sample loader due to
 * an invalid sigma delta compression stream.
 */

TEST(test_fuzzer_sym_bad_sigmadelta)
{
	xmp_context opaque;
	int ret;

	opaque = xmp_create_context();
	ret = xmp_load_module(opaque, "data/f/load_sym_bad_sigmadelta.sym");
	fail_unless(ret == -XMP_ERROR_LOAD, "module load");

	xmp_free_context(opaque);
}
END_TEST
