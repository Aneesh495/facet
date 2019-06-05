#ifndef FACET_OBJ_H
#define FACET_OBJ_H

#include "facet_types.h"

FacetMesh* facet_obj_read(const char* filepath);
bool facet_obj_write(const FacetMesh* mesh, const char* filepath);

#endif // FACET_OBJ_H
