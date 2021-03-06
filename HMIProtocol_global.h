/*************************************************************/
/* AUTOR: GabiAndi                                           */
/* FECHA: 14/01/2022                                         */
/*                                                           */
/* DESCRIPCION:                                              */
/* Encabezado automático que añade opciones al compilador    */
/* dependiendo la plataforma de destino.                     */
/*************************************************************/

#ifndef HMIPROTOCOL_GLOBAL_H
#define HMIPROTOCOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HMIPROTOCOL_LIBRARY)
#  define HMIPROTOCOL_EXPORT Q_DECL_EXPORT
#else
#  define HMIPROTOCOL_EXPORT Q_DECL_IMPORT
#endif

#endif // HMIPROTOCOL_GLOBAL_H
