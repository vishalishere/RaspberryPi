#ifndef RPICOMM_GLOBAL_H
#define RPICOMM_GLOBAL_H

#pragma once

#if defined(RPICOMM_LIBRARY)
#  define RPICOMMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RPICOMMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RPICOMM_GLOBAL_H