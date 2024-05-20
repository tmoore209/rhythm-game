#include "SceneManager.hpp"
#include "Metrohop.hpp"
#include "BatterScene.hpp"

namespace SceneManager {
    
    // Main menu button callback
    void cb_Metrohop() {
        SceneManager::ReplaceScene(SCENE_METROHOP);
    }

    // Main menu button callback
    void cb_Batter() {
        SceneManager::ReplaceScene(SCENE_BATTER);
    }

    Scene* CreateScene_MainMenu() {
        Scene* s = new Scene();
        s->name = "Main Menu";
        auto b1 = new TextButton(200, 300-10, "Metrohop", cb_Metrohop);
        auto b2 = new TextButton(600, 300-10, "Batter", cb_Batter);
        b1->right = b2;
        b2->left = b1;
        s->children.push_back(b1);
        s->children.push_back(b2);
        s->firstFocused = b1;
        return s;
    }

    // Replace current scene by enum
    void ReplaceScene(SCENES scene) {
        Scene* s;
        switch (scene) {
            case SCENE_MAINMENU:
                s = CreateScene_MainMenu();
                break;
            case SCENE_METROHOP:
                s = new Metrohop();
                break;
            case SCENE_BATTER:
                s = new BatterScene();
                break;
            default:
                exit(1);
        }
        ReplaceScene(s);
    }
    
    // Replace current scene by pointer to already-constructed scene
    void ReplaceScene(Scene* scene) {
        if(currentScene) {
            free(currentScene);
        }
        currentScene = scene;
        FocusStack::Clear();
        FocusStack::Push(currentScene->firstFocused);
    }

    Scene* GetCurrent() {
        return currentScene;
    }
}