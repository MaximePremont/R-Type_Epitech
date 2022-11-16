if (NOT EXISTS "/home/ahmed/tek/tek3/B-CPP-500-LYN-5-1-rtype-maxime.premont/docs/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/home/ahmed/tek/tek3/B-CPP-500-LYN-5-1-rtype-maxime.premont/docs/install_manifest.txt\"")
endif(NOT EXISTS "/home/ahmed/tek/tek3/B-CPP-500-LYN-5-1-rtype-maxime.premont/docs/install_manifest.txt")

file(READ "/home/ahmed/tek/tek3/B-CPP-500-LYN-5-1-rtype-maxime.premont/docs/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /usr/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

