TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Animator/Animation.cpp \
        Animator/Animator.cpp \
        Animator/AnimatorConnection.cpp \
        Animator/AnimatorNode.cpp \
        Animator/AnimatorVariables.cpp \
        Animator/ConnectionCondition.cpp \
        Animator/Frame.cpp \
        Entity/Damagable.cpp \
        Entity/Entity.cpp \
        Entity/EntityAnimated.cpp \
        Entity/Hitbox.cpp \
        Entity/Player.cpp \
        GFXE/BufferQueueElement.cpp \
        GFXE/GFXE.cpp \
        Scene/Scene.cpp \
        Scene/Terrain.cpp \
        main.cpp

HEADERS += \
    Animator/Animation.h \
    Animator/Animator.h \
    Animator/AnimatorConnection.h \
    Animator/AnimatorNode.h \
    Animator/AnimatorVariables.h \
    Animator/ConnectionCondition.h \
    Animator/Frame.h \
    Bonus.h \
    Containers.h \
    Entity/Damagable.h \
    Entity/Entity.h \
    Entity/EntityAnimated.h \
    Entity/Hitbox.h \
    Entity/Player.h \
    GFXE/BufferQueueElement.h \
    GFXE/GFXE.h \
    Scene/Scene.h \
    Scene/Terrain.h


