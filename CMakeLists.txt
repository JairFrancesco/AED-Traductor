cmake_minimum_required(VERSION 2.8.8)
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()
if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW) # CMake 3.0
endif()
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # CMake 3.1
endif()

add_compile_options(-std=c++11) # CMake 2.8.12 or newer

project(AED_Diccionario)

find_package(VTK COMPONENTS
  #vtkCommonCore
  #vtkFiltersSources
  #vtkGUISupportQt
)
include(${VTK_USE_FILE})

if("${VTK_QT_VERSION}" STREQUAL "")
  message(FATAL_ERROR "VTK was not built with Qt")
endif()

set( Srcs main.cpp GUI4.cpp)

set( Hdrs
    GUI4.h
    DataStructures/AVL.h
    DataStructures/NodoArbol.h
    Complementary/palabra.h
    DataStructures/rbnode.h
    DataStructures/rbtree.h
    DataStructures/cola.h
    DataStructures/nodo.h
    DataStructures/pila.h
    DataStructures/Fheap.h
    DataStructures/NodoF.h
    DataStructures/Lista.h
    DataStructures/arbolbb.h
    DataStructures/BinomialHeap.h
    Complementary/searchstructure.h
    Complementary/levenshtein.h)

set( MOC_Hdrs
    GUI4.h
    DataStructures/AVL.h
    DataStructures/NodoArbol.h
    Complementary/palabra.h
    DataStructures/rbnode.h
    DataStructures/arbolbb.h
    DataStructures/rbtree.h
    DataStructures/cola.h
    DataStructures/nodo.h
    DataStructures/pila.h
    DataStructures/Fheap.h
    DataStructures/NodoF.h
    DataStructures/Lista.h
    DataStructures/BinomialHeap.h
    Complementary/searchstructure.h
    Complementary/levenshtein.h)

set( UIs GUI4.ui )

# Use the include path and library for Qt that is used by VTK.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  Complementary
  DataStructures

)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

if(VTK_QT_VERSION VERSION_GREATER "4")
  find_package(Qt5 COMPONENTS Widgets)
  qt5_wrap_ui(UI_Srcs ${UIs})

  add_executable(AED_Diccionario
    MACOSX_BUNDLE  ${Srcs} ${Hdrs} ${UI_Srcs} ${MOC_Hdrs})
  qt5_use_modules(AED_Diccionario Core Gui Widgets)
  target_link_libraries(AED_Diccionario ${VTK_LIBRARIES})
else()
  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
  # Use what VTK built with
  set(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")
  set(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
  set(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
  qt4_wrap_ui(UI_Srcs ${UIs})

  add_executable(AED_Diccionario MACOSX_BUNDLE ${Srcs} ${Hdrs} ${UI_Srcs} ${MOC_Hdrs})
  target_link_libraries(AED_Diccionario
    ${QT_LIBRARIES}
    ${VTK_LIBRARIES}
  )
endif()
