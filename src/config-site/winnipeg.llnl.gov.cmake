#/usr/gapps/visit/thirdparty_shared/3.0.1/cmake/3.9.3/linux-x86_64_gcc-4.8/bin/cmake
##
## ./build_visit3_0_1 generated host.cmake
## created: Thu Jul 11 16:05:27 PDT 2019
## system: Linux winnipeg.llnl.gov 5.0.8-1.el7.elrepo.x86_64 #1 SMP Wed Apr 17 10:11:44 EDT 2019 x86_64 x86_64 x86_64 GNU/Linux
## by: brugger1

##
## Setup VISITHOME & VISITARCH variables.
##
SET(VISITHOME /usr/gapps/visit/thirdparty_shared/3.0.1)
SET(VISITARCH linux-x86_64_gcc-4.8)
VISIT_OPTION_DEFAULT(VISIT_SLIVR TRUE TYPE BOOL)

## Compiler flags.
##
VISIT_OPTION_DEFAULT(VISIT_C_COMPILER gcc TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_CXX_COMPILER g++ TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_FORTRAN_COMPILER no TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_C_FLAGS " -m64 -fPIC -fvisibility=hidden" TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_CXX_FLAGS " -m64 -fPIC -fvisibility=hidden" TYPE STRING)

##
## Parallel Build Setup.
##
VISIT_OPTION_DEFAULT(VISIT_PARALLEL ON TYPE BOOL)
## (configured w/ mpi compiler wrapper)
VISIT_OPTION_DEFAULT(VISIT_MPI_COMPILER /usr/gapps/visit/thirdparty_shared/3.0.1/mpich/3.0.4/linux-x86_64_gcc-4.8/bin/mpicc TYPE FILEPATH)

##
## VisIt Thread Option
##
VISIT_OPTION_DEFAULT(VISIT_THREAD OFF TYPE BOOL)

##############################################################
##
## Database reader plugin support libraries
##
## The HDF4, HDF5 and NetCDF libraries must be first so that
## their libdeps are defined for any plugins that need them.
##
## For libraries with LIBDEP settings, order matters.
## Libraries with LIBDEP settings that depend on other
## Library's LIBDEP settings must come after them.
##############################################################
##

##
## ZLIB
##
VISIT_OPTION_DEFAULT(VISIT_ZLIB_DIR ${VISITHOME}/zlib/1.2.8/${VISITARCH})

##
## OPENSSL 
##
VISIT_OPTION_DEFAULT(VISIT_OPENSSL_DIR ${VISITHOME}/openssl/1.0.2j/${VISITARCH})

##
## Python
##
VISIT_OPTION_DEFAULT(VISIT_PYTHON_DIR ${VISITHOME}/python/2.7.14/${VISITARCH})

##
## Qt
##
SETUP_APP_VERSION(QT 5.10.1)
VISIT_OPTION_DEFAULT(VISIT_QT_DIR ${VISITHOME}/qt/${QT_VERSION}/${VISITARCH})

##
## QWT
##
SETUP_APP_VERSION(QWT 6.1.2)
VISIT_OPTION_DEFAULT(VISIT_QWT_DIR ${VISITHOME}/qwt/${QWT_VERSION}/${VISITARCH})

##
## ISPC
##
VISIT_OPTION_DEFAULT(VISIT_ISPC_DIR ${VISITHOME}/ispc/1.9.2/${VISITARCH})

##
## TBB
##
VISIT_OPTION_DEFAULT(TBB_ROOT ${VISITHOME}/tbb/tbb2018_20171205oss/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_TBB_DIR ${VISITHOME}/tbb/tbb2018_20171205oss/${VISITARCH})

##
## EMBREE
##
VISIT_OPTION_DEFAULT(VISIT_EMBREE_DIR ${VISITHOME}/embree/3.2.0/${VISITARCH})

##
## OSPRay
##
VISIT_OPTION_DEFAULT(VISIT_OSPRAY ON TYPE BOOL)
SETUP_APP_VERSION(OSPRAY 1.6.1)
VISIT_OPTION_DEFAULT(VISIT_OSPRAY_DIR ${VISITHOME}/ospray/1.6.1/${VISITARCH})

##
## VTK
##
SETUP_APP_VERSION(VTK 8.1.0)
VISIT_OPTION_DEFAULT(VISIT_VTK_DIR ${VISITHOME}/vtk/${VTK_VERSION}/${VISITARCH})

##
## MPICH
##
# Give VisIt information so it can install MPI into the binary distribution.
VISIT_OPTION_DEFAULT(VISIT_MPICH_DIR ${VISITHOME}/mpich/3.0.4/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_MPICH_INSTALL ON TYPE BOOL)

# Tell VisIt the parallel compiler so it can deduce parallel flags
VISIT_OPTION_DEFAULT(VISIT_MPI_COMPILER ${VISIT_MPICH_DIR}/bin/mpicc TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_PARALLEL ON TYPE BOOL)

##
## SZIP
##
VISIT_OPTION_DEFAULT(VISIT_SZIP_DIR ${VISITHOME}/szip/2.1/${VISITARCH})

##
## HDF5
##
VISIT_OPTION_DEFAULT(VISIT_HDF5_DIR ${VISITHOME}/hdf5/1.8.14/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF5_MPI_DIR ${VISITHOME}/hdf5_mpi/1.8.14/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF5_LIBDEP ${VISITHOME}/szip/2.1/${VISITARCH}/lib sz ${VISITHOME}/zlib/1.2.8/${VISITARCH}/lib z TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_HDF5_MPI_LIBDEP ${VISITHOME}/szip/2.1/${VISITARCH}/lib sz ${VISITHOME}/zlib/1.2.8/${VISITARCH}/lib z TYPE STRING)

##
## ADIOS
## (configured w/ mpi compiler wrapper)
##
SETUP_APP_VERSION(ADIOS 1.13.1)
VISIT_OPTION_DEFAULT(VISIT_ADIOS_DIR ${VISITHOME}/adios/${ADIOS_VERSION}/${VISITARCH})

##
## ADIOS2
##
SETUP_APP_VERSION(ADIOS2 2.4.0)
VISIT_OPTION_DEFAULT(VISIT_ADIOS2_DIR ${VISITHOME}/adios2-ser/${ADIOS2_VERSION}/${VISITARCH})
## (configured w/ mpi compiler wrapper)
VISIT_OPTION_DEFAULT(VISIT_ADIOS2_PAR_DIR ${VISITHOME}/adios2-par/${ADIOS2_VERSION}/${VISITARCH})

##
## AdvIO
##
VISIT_OPTION_DEFAULT(VISIT_ADVIO_DIR ${VISITHOME}/AdvIO/1.2/${VISITARCH})

##
## BOOST
##
SETUP_APP_VERSION(BOOST 1_67_0)
VISIT_OPTION_DEFAULT(VISIT_BOOST_DIR ${VISITHOME}/boost/${BOOST_VERSION}/${VISITARCH})

##
## Boxlib
##
VISIT_OPTION_DEFAULT(VISIT_BOXLIB_DIR ${VISITHOME}/boxlib/1.3.5/${VISITARCH})

##
## CFITSIO
##
VISIT_OPTION_DEFAULT(VISIT_CFITSIO_DIR ${VISITHOME}/cfitsio/3006/${VISITARCH})

##
## CGNS
##
VISIT_OPTION_DEFAULT(VISIT_CGNS_DIR ${VISITHOME}/cgns/3.2.1/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_CGNS_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## Conduit
##
VISIT_OPTION_DEFAULT(VISIT_CONDUIT_DIR ${VISITHOME}/conduit/v0.4.0/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_CONDUIT_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## GDAL
##
VISIT_OPTION_DEFAULT(VISIT_GDAL_DIR ${VISITHOME}/gdal/2.2.4/${VISITARCH})

##
## H5Part
##
SETUP_APP_VERSION(H5PART 1.6.6)
VISIT_OPTION_DEFAULT(VISIT_H5PART_DIR ${VISITHOME}/h5part/${H5PART_VERSION}/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_H5PART_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## HDF4
##
VISIT_OPTION_DEFAULT(VISIT_HDF4_DIR ${VISITHOME}/hdf4/4.2.5/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF4_LIBDEP ${VISITHOME}/szip/2.1/${VISITARCH}/lib sz ${VISITHOME}/vtk/${VTK_VERSION}/${VISITARCH}/lib vtkjpeg-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION} TYPE STRING)

##
## Ice-T
##
VISIT_OPTION_DEFAULT(VISIT_ICET_DIR ${VISITHOME}/icet/77c708f9090236b576669b74c53e9f105eedbd7e/${VISITARCH})

##
## LLVM
##
VISIT_OPTION_DEFAULT(VISIT_LLVM_DIR ${VISITHOME}/llvm/5.0.0/${VISITARCH})

##
## MFEM 
##
VISIT_OPTION_DEFAULT(VISIT_MFEM_DIR ${VISITHOME}/mfem/3.4/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_MFEM_INCDEP CONDUIT_INCLUDE_DIR TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_MFEM_LIBDEP ${VISIT_CONDUIT_LIBDEP} ${VISITHOME}/zlib/1.2.8/${VISITARCH}/lib z TYPE STRING)

##
## Mili
##
VISIT_OPTION_DEFAULT(VISIT_MILI_DIR ${VISITHOME}/mili/15.1/${VISITARCH})

##
## MOAB 
##
VISIT_OPTION_DEFAULT(VISIT_MOAB_DIR ${VISITHOME}/moab/4.9.2-RC0/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_MOAB_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_MOAB_MPI_DIR ${VISITHOME}/moab_mpi/4.9.2-RC0/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_MOAB_MPI_LIBDEP HDF5_MPI_LIBRARY_DIR hdf5_mpi ${VISIT_HDF5_MPI_LIBDEP} TYPE STRING)
##

##
## NetCDF
##
VISIT_OPTION_DEFAULT(VISIT_NETCDF_DIR ${VISITHOME}/netcdf/4.1.1/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_NETCDF_LIBDEP HDF5_LIBRARY_DIR hdf5_hl HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## OpenEXR
##
VISIT_OPTION_DEFAULT(VISIT_OPENEXR_DIR ${VISITHOME}/openexr/2.2.0/${VISITARCH})

##
## P7ZIP
##
VISIT_OPTION_DEFAULT(VISIT_SEVEN_ZIP_DIR ${VISITHOME}/p7zip/16.02/${VISITARCH})

##
## PIDX
##
SETUP_APP_VERSION(PIDX 0.9.3)
VISIT_OPTION_DEFAULT(VISIT_PIDX_DIR ${VISITHOME}/pidx/${PIDX_VERSION}/${VISITARCH})

##
## Silo
##
VISIT_OPTION_DEFAULT(VISIT_SILO_DIR ${VISITHOME}/silo/4.10.2/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_SILO_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} ZLIB_LIBRARY_DIR z TYPE STRING)

##
## VTKM
##
VISIT_OPTION_DEFAULT(VISIT_VTKM_DIR ${VISITHOME}/vtkm/0d141c/${VISITARCH})

##
## VTKH
##
VISIT_OPTION_DEFAULT(VISIT_VTKH_DIR ${VISITHOME}/vtkh/2ce3fa/${VISITARCH})

##
## Xdmf
##
VISIT_OPTION_DEFAULT(VISIT_XDMF_DIR ${VISITHOME}/Xdmf/2.1.1/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_XDMF_LIBDEP HDF5_LIBRARY_DIR hdf5  VTK_LIBRARY_DIRS vtklibxml2-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}  TYPE STRING)

