cmake_minimum_required (VERSION 3.14)

set (EXTERNAL_PROJECTS ncurses sndio sdl boost capstone gsl zlib png gzip cppcoro)

foreach (EXTERNAL_PROJECT ${EXTERNAL_PROJECTS})

  set (DIR_PROJECT_OUT ${DIR_ROOT_OUT}/${EXTERNAL_PROJECT})

  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DIR_PROJECT_OUT}/lib)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIR_PROJECT_OUT}/lib)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR_PROJECT_OUT}/bin)  

  add_subdirectory (${EXTERNAL_PROJECT})

endforeach ()
