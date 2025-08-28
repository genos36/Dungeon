# File generato automaticamente da update_extra.sh
# Modifiche MANUALI sopra il commento '###' saranno preservate
# Tutto sotto sara' sovrascritto!

### INIZIO AREA MANUALE ###
# File generato automaticamente da update_extra.sh
# Modifiche MANUALI sopra il commento '###' saranno preservate
# Tutto sotto sara' sovrascritto!


### INIZIO AREA AUTOMATICA ###
target_sources(${PROJECT_NAME} PRIVATE
    src/Utilities/Singleton.cpp
    src/entities/Entity.cpp
    src/main.cpp
    src/render/AnimationSystem.cpp
    src/render/BatchRenderLayerSystem.cpp
    src/render/BatchRenderer.cpp
    src/render/Camera.cpp
    src/render/CulledRenderSystem.cpp
    src/render/CullingStrategy/ConservativeFrustumCulling.cpp
    src/render/CullingStrategy/DistanceCullingStrategy.cpp
    src/render/CullingStrategy/NoCullingStrategy.cpp
    src/render/CullingStrategy/ZoomAwareCullingStrategy.cpp
    src/render/LayeredRenderSystem.cpp
    src/render/RenderComponent.cpp
    src/render/RenderSystem.cpp
    src/render/TextureLoader.cpp
    src/render/TextureLoaderStrategy/AbstractTextureLoader.cpp
    src/render/TextureLoaderStrategy/SingleTextureLoader.cpp
    src/render/TextureRegistry.cpp
    include/Game.h
    include/Utilities/Singleton.h
    include/communication/AbstactCommunicationService.h
    include/entities/Contoller.h
    include/entities/Entity.h
    include/map/GameMap.h
    include/map/Tile.h
    include/render/AnimationSystem.h
    include/render/BatchRenderLayerSystem.h
    include/render/BatchRenderer.h
    include/render/Camera.h
    include/render/CulledRenderSystem.h
    include/render/CullingStrategy/AbstractCullingStrategy.h
    include/render/CullingStrategy/ConservativeFrustumCulling.h
    include/render/CullingStrategy/DistanceCullingStrategy.h
    include/render/CullingStrategy/NoCullingStrategy.h
    include/render/CullingStrategy/ZoomAwareCullingStrategy.h
    include/render/LayeredRenderSystem.h
    include/render/RenderComponent.h
    include/render/RenderSystem.h
    include/render/TextureLoader.h
    include/render/TextureLoaderStrategy/AbstractTextureLoader.h
    include/render/TextureLoaderStrategy/SingleTextureLoader.h
    include/render/TextureLoaderStrategy/TextureType.h
    include/render/TextureRegistry.h
    include/weapons/Weapon.h
)
