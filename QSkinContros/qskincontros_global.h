#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QSKINCONTROS_LIB)
#  define QSKINCONTROS_EXPORT Q_DECL_EXPORT
# else
#  define QSKINCONTROS_EXPORT Q_DECL_IMPORT
# endif
#else
# define QSKINCONTROS_EXPORT
#endif
