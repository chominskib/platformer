#ifndef ENV_CONSTANTS_HPP
#define ENV_CONSTANTS_HPP

#include "events.hpp"
#include "render.hpp"

extern double g;
extern double platform_friction_coefficient;
extern double drag_coefficient;
extern double air_manouverability;
extern std::string version;

class Bookkeeper;
class AssetsMgr;

extern Bookkeeper global_bookkeeper;
extern AssetsMgr global_assetsmgr;

#endif
