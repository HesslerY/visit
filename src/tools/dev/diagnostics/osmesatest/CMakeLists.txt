# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#   Kathleen Biagas, Wed Oct 22 14:20:27 MST 2014
#   Send 'diagnostics/osmesatest' type argument to VISIT_TOOLS_ADD_FOLDER.
#
#****************************************************************************

SET(TARGETS osmesatest_ser osmesavtktest_ser)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_BINARY_DIR}/include
${VISIT_SOURCE_DIR}/include
${OSMESA_INCLUDE_DIR}
${VTK_INCLUDE_DIRS}
)

LINK_DIRECTORIES(
${LIBRARY_OUTPUT_DIRECTORY}
)

SET(REQUIRED_VTK_LIBS
vtkCommonCore 
vtkCommonDataModel
vtkCommonExecutionModel
vtkFiltersGeometry 
vtkFiltersHybrid
vtkFiltersSources
vtkIOImage
vtkRenderingCore
vtkRenderingOpenGL2
vtkRenderingFreeType 
vtkInteractionStyle 
)

IF(NOT WIN32)
    SET(LIBDL dl)
    SET(PTHREAD pthread)
ENDIF(NOT WIN32)

ADD_EXECUTABLE(osmesatest_ser osmesatest.cpp)
TARGET_LINK_LIBRARIES(osmesatest_ser ${VISIT_EXE_LINKER_FLAGS} ${OSMESA_LIBRARIES} ${LIBDL} ${PTHREAD})

ADD_EXECUTABLE(osmesavtktest_ser osmesavtktest.cpp)
TARGET_LINK_LIBRARIES(osmesavtktest_ser ${VISIT_EXE_LINKER_FLAGS} visit_vtk_offscreen visitcommon ${REQUIRED_VTK_LIBS} ${LIBDL} ${PTHREAD})

IF(VISIT_PARALLEL)
    ADD_PARALLEL_EXECUTABLE(osmesatest_par osmesatest.cpp)
    PARALLEL_EXECUTABLE_LINK_LIBRARIES(osmesatest_par ${OSMESA_LIBRARIES} ${LIBDL} ${PTHREAD})

    ADD_PARALLEL_EXECUTABLE(osmesavtktest_par osmesavtktest.cpp)
    PARALLEL_EXECUTABLE_LINK_LIBRARIES(osmesavtktest_par visit_vtk_offscreen visitcommon ${REQUIRED_VTK_LIBS} ${LIBDL} ${PTHREAD})

    SET(TARGETS ${TARGETS} osmesatest_par osmesavtktest_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_TARGETS(${TARGETS})
VISIT_TOOLS_ADD_FOLDER(diagnostics/osmesatest ${TARGETS})
