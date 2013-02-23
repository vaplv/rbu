#ifndef RBU_H
#define RBU_H

#include <rb/rb_types.h>
#include <snlsys/ref_count.h>
#include <snlsys/snlsys.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef NDEBUG
  #include <assert.h>
  #define RBU(func) ASSERT(0 == rbu_##func)
#else
  #define RBU(func) rbu_##func
#endif

#if defined(RBU_SHARED_BUILD)
  #define RBU_API EXPORT_SYM
#else
  #define RBU_API IMPORT_SYM
#endif

struct rbi;
struct rb_buffer;
struct rb_context;
struct rb_vertex_array;

/*******************************************************************************
 *
 * Render backend utils data structure. Internal data are `private' and
 * consequently may not be accessed directly.
 *
 ******************************************************************************/
struct rbu_geometry {
  struct ref ref;
  const struct rbi* rbi;
  struct rb_context* ctxt;
  struct rb_buffer* vertex_buffer;
  struct rb_buffer* index_buffer;
  struct rb_vertex_array* vertex_array;
  size_t nb_vertices;
  enum rb_primitive_type primitive_type;
};

/* Constant defining a `NULL' geometry */
static const struct rbu_geometry RBU_GEOMETRY_NULL = { .rbi = NULL };

/* Macro defining whether or not the geometry is valid */
#define RBU_GEOMETRY_IS_VALID(geom) ((geom).rbi != NULL)

/*******************************************************************************
 *
 * Render backend utils functions prototypes.
 *
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/* Non textured 2D quad. The vertex position attrib is bound to location 0 */
RBU_API int
rbu_init_quad
  (const struct rbi* rbi,
   struct rb_context* ctxt,
   float x,
   float y,
   float width,
   float height,
   struct rbu_geometry* quad);

/* 2D circle. The vertex position attrib is bound to location 0 */
RBU_API int
rbu_init_circle
  (const struct rbi* rbi,
   struct rb_context* ctxt,
   unsigned int npoints,
   float pos[2],
   float radius,
   struct rbu_geometry* circle);

/* Parallelepiped. The vertex position attrib is bound to location 0 */
RBU_API int
rbu_init_parallelepiped
  (const struct rbi* rbi,
   struct rb_context* ctxt,
   float pos[3],
   float size[3],
   bool wireframe,
   struct rbu_geometry* cube);

/* Closed cylinder. The vertex position attrib is bound to location 0 */
RBU_API int
rbu_init_cylinder
  (const struct rbi* rbi,
   struct rb_context* ctxt,
   unsigned int nslices, /* Ceil to even value */
   float base_radius,
   float top_radius,
   float height,
   float pos[3],
   struct rbu_geometry* cylinder);

RBU_API int
rbu_geometry_ref_get
  (struct rbu_geometry* geom);

RBU_API int
rbu_geometry_ref_put
  (struct rbu_geometry* geom);

RBU_API int
rbu_draw_geometry
  (struct rbu_geometry* geom);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* RBU_H */

