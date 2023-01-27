#include "Assets.hpp"

Assets& Assets::Instance()
{
    static Assets assets;
    return assets;
}

void Assets::loadAssets()
{
    loadImages();
    loadFonts();
}

void Assets::loadImages()
{
    RenderWindow &rw = RenderWindow::Instance();
    img_Test = rw.loadTexture("Assets/images/TestSprite.png");
    img_Background = rw.loadTexture("Assets/images/ResourceManagerBackground.png");
    img_GraphView = rw.loadTexture("Assets/images/GraphView.png");
    img_ListView = rw.loadTexture("Assets/images/ListView.png");
    img_GraphBorders = rw.loadTexture("Assets/images/GraphBorders.png");
    img_ListBorders = rw.loadTexture("Assets/images/OverList.png");
    img_ScrollArea = rw.loadTexture("Assets/images/ScrollBarArea.png");
    img_ScrollBarSmall = rw.loadTexture("Assets/images/ScrollBar.png");
    img_ScrollBarMed = rw.loadTexture("Assets/images/ScrollBarMedium.png");
    img_ScrollBarLarge = rw.loadTexture("Assets/images/ScrollBarLarge.png");
    img_ArrowRight = rw.loadTexture("Assets/images/ArrowRight.png");
    img_ArrowBottomLeft = rw.loadTexture("Assets/images/ArrowBottomLeft.png");
    img_ArrowBottomRight = rw.loadTexture("Assets/images/ArrowBottomRight.png");
    img_ArrowDown = rw.loadTexture("Assets/images/ArrowDown.png");
    img_ArrowLeft = rw.loadTexture("Assets/images/ArrowLeft.png");
    img_ArrowTopLeft = rw.loadTexture("Assets/images/ArrowTopLeft.png");
    img_ArrowTopRight = rw.loadTexture("Assets/images/ArrowTopRight.png");
    img_ArrowUp = rw.loadTexture("Assets/images/ArrowUp.png");
    img_circleNode = rw.loadTexture("Assets/images/ResourceNodeCircle.png");
    img_selectedCircleNode = rw.loadTexture("Assets/images/SelectedResourceNodeCircle.png");
    img_craftButton = rw.loadTexture("Assets/images/CraftButton1.png");	
    img_craftButtonPressed = rw.loadTexture("Assets/images/CraftButton2.png");
    img_StartMenuBackground = rw.loadTexture("Assets/images/StartMenuBackground.png");
    img_StartMenuButton = rw.loadTexture("Assets/images/StartButton1.png");
    img_StartMenuButtonPressed = rw.loadTexture("Assets/images/StartButton2.png");
    img_ExitButton = rw.loadTexture("Assets/images/ExitButton1.png");
    img_ExitButtonPressed = rw.loadTexture("Assets/images/ExitButton2.png");
    img_GameSky = rw.loadTexture("Assets/images/GameSky.png");
    img_GameBackground = rw.loadTexture("Assets/images/GameBackground.png");
    img_GameForeground = rw.loadTexture("Assets/images/GameForeground.png");
    img_FloorTile = rw.loadTexture("Assets/images/FloorTile.png");
    img_Ore = rw.loadTexture("Assets/images/Ore.png");
    img_PlayerRight = rw.loadTexture("Assets/images/characters/WelderRight.png");
    img_PlayerLeft = rw.loadTexture("Assets/images/characters/WelderLeft.png");
    img_InventoryUI = rw.loadTexture("Assets/images/InventoryUI.png");
    img_Yellow = rw.loadTexture("Assets/images/Yellow.png");
    img_White = rw.loadTexture("Assets/images/White.png");
    img_SpikesUI = rw.loadTexture("Assets/images/SpikesUI.png");
    img_GunUI = rw.loadTexture("Assets/images/GunUI.png");
    img_TurretUI = rw.loadTexture("Assets/images/TurretUI.png");
    img_BombUI = rw.loadTexture("Assets/images/BombUI.png");
    img_HandCannonUI = rw.loadTexture("Assets/images/HandCannonUI.png");
    img_CannonUI = rw.loadTexture("Assets/images/CannonUI.png");
    img_TransparentTurretRight = rw.loadTexture("Assets/images/TransparentTurretRight.png");
    img_TransparentTurretLeft = rw.loadTexture("Assets/images/TransparentTurretLeft.png");
    img_ScrapPileTransparent = rw.loadTexture("Assets/images/ScrapPileTransparent.png");
    img_ScrapPile = rw.loadTexture("Assets/images/ScrapPile.png");
    img_GunPowder = rw.loadTexture("Assets/images/GunPowder.png");
    img_BombPreview = rw.loadTexture("Assets/images/BombPreview.png");
    img_CannonPreviewRight = rw.loadTexture("Assets/images/CannonPreviewRight.png");
    img_CannonPreviewLeft = rw.loadTexture("Assets/images/CannonPreviewLeft.png");
    img_GameOverBackground = rw.loadTexture("Assets/images/EndMenu.png");
    img_ContinueButton = rw.loadTexture("Assets/images/ContinueButton1.png");
    img_ContinueButtonPressed = rw.loadTexture("Assets/images/ContinueButton2.png");
    img_CaveRight = rw.loadTexture("Assets/images/CaveRight.png");
    img_CaveLeft = rw.loadTexture("Assets/images/CaveLeft.png");
    img_WaveMarker = rw.loadTexture("Assets/images/WaveMarker.png");
    img_WaveBar = rw.loadTexture("Assets/images/WaveBar.png");
    img_Heart = rw.loadTexture("Assets/images/Heart.png");


    for (int i = 1; i <= 4; i++)
    {
        std::string bulletLeftPath = "Assets/images/BulletLeft" + std::to_string(i) + ".png";
        std::string bulletRightPath = "Assets/images/BulletRight" + std::to_string(i) + ".png";
        imgs_bulletDestroyLeft.push_back(rw.loadTexture(bulletLeftPath.c_str()));
        imgs_bulletDestroyRight.push_back(rw.loadTexture(bulletRightPath.c_str()));
    }

    for (int i = 1; i <= 5; i++)
    {
        std::string turretDestroyLeftPath = "Assets/images/TurretDestroyLeft" + std::to_string(i) + ".png";
        std::string turretDestroyRightPath = "Assets/images/TurretDestroyRight" + std::to_string(i) + ".png";
        imgs_TurretDestroyLeft.push_back(rw.loadTexture(turretDestroyLeftPath.c_str()));
        imgs_TurretDestroyRight.push_back(rw.loadTexture(turretDestroyRightPath.c_str()));
    }

    for (int i = 1; i <= 6; i++)
    {
        std::string missileTurretLeftPath = "Assets/images/MissileTurretLeft" + std::to_string(i) + ".png";
        std::string missileTurretRightPath = "Assets/images/MissileTurretRight" + std::to_string(i) + ".png";
        std::string turretLeftPath = "Assets/images/TurretLeft" + std::to_string(i) + ".png";
        std::string turretRightPath = "Assets/images/TurretRight" + std::to_string(i) + ".png";
        std::string alienDieLeftPath = "Assets/images/characters/AlienDieLeft" + std::to_string(i) + ".png";
        std::string alienDieRightPath = "Assets/images/characters/AlienDieRight" + std::to_string(i) + ".png";
        std::string playerDieLeftPath = "Assets/images/characters/WelderDieLeft" + std::to_string(i) + ".png";
        std::string playerDieRightPath = "Assets/images/characters/WelderDieRight" + std::to_string(i) + ".png";
        std::string missileTurretDestroyRightPath = "Assets/images/MissileTurretDestroyRight" + std::to_string(i) + ".png";
        std::string missileTurretDestroyLeftPath = "Assets/images/MissileTurretDestroyLeft" + std::to_string(i) + ".png";
        imgs_turretRight.push_back(rw.loadTexture(turretRightPath.c_str()));
        imgs_turretLeft.push_back(rw.loadTexture(turretLeftPath.c_str()));
        imgs_CannonLeft.push_back(rw.loadTexture(missileTurretLeftPath.c_str()));
        imgs_CannonRight.push_back(rw.loadTexture(missileTurretRightPath.c_str()));
        imgs_PlayerDieRight.push_back(rw.loadTexture(playerDieRightPath.c_str()));
        imgs_PlayerDieLeft.push_back(rw.loadTexture(playerDieLeftPath.c_str()));
        imgs_AlienDieRight.push_back(rw.loadTexture(alienDieRightPath.c_str()));
        imgs_AlienDieLeft.push_back(rw.loadTexture(alienDieLeftPath.c_str()));
        imgs_MissileTurretDestroyLeft.push_back(rw.loadTexture(missileTurretDestroyLeftPath.c_str()));
        imgs_MissileTurretDestroyRight.push_back(rw.loadTexture(missileTurretDestroyRightPath.c_str()));
    }

    for (int i = 1; i <= 7; i++)
    {
        std::string alienAttackRightPath = "Assets/images/characters/AlienAttackRight" + std::to_string(i) + ".png";
        std::string alienAttackLeftPath = "Assets/images/characters/AlienAttackLeft" + std::to_string(i) + ".png";
        std::string alienAttackRightDamagePath = "Assets/images/characters/AlienAttackRightDamage" + std::to_string(i) + ".png";
        std::string alienAttackLeftDamagePath = "Assets/images/characters/AlienAttackLeftDamage" + std::to_string(i) + ".png";
        imgs_AlienAttackRightDamage.push_back(rw.loadTexture(alienAttackRightDamagePath.c_str()));
        imgs_AlienAttackLeftDamage.push_back(rw.loadTexture(alienAttackLeftDamagePath.c_str()));
        imgs_AlienAttackRight.push_back(rw.loadTexture(alienAttackRightPath.c_str()));
        imgs_AlienAttackLeft.push_back(rw.loadTexture(alienAttackLeftPath.c_str()));
    }

    for (int i = 1; i <= 8; i++)
    {
        std::string playerWalkLeftPath = "Assets/images/characters/WelderWalkLeft" + std::to_string(i) + ".png";
        std::string playerWalkRightPath = "Assets/images/characters/WelderWalkRight" + std::to_string(i) + ".png";
        imgs_PlayerWalkLeft.push_back(rw.loadTexture(playerWalkLeftPath.c_str()));
        imgs_PlayerWalkRight.push_back(rw.loadTexture(playerWalkRightPath.c_str()));
        std::string enemyWalkLeftPath = "Assets/images/characters/AlienWalkLeft" + std::to_string(i) + ".png";
        std::string enemyWalkRightPath = "Assets/images/characters/AlienWalkRight" + std::to_string(i) + ".png";
        imgs_EnemyWalkLeft.push_back(rw.loadTexture(enemyWalkLeftPath.c_str()));
        imgs_EnemyWalkRight.push_back(rw.loadTexture(enemyWalkRightPath.c_str()));
        std::string alienWalkLeftDamagePath = "Assets/images/characters/AlienWalkLeftDamage" + std::to_string(i) + ".png";
        std::string alienWalkRightDamagePath = "Assets/images/characters/AlienWalkRightDamage" + std::to_string(i) + ".png";
        imgs_AlienWalkLeftDamage.push_back(rw.loadTexture(alienWalkLeftDamagePath.c_str()));
        imgs_AlienWalkRightDamage.push_back(rw.loadTexture(alienWalkRightDamagePath.c_str()));
    }

    for (int i = 1; i <= 9; i++)
    {
        std::string bigBulletLeftPath = "Assets/images/BigBulletLeft" + std::to_string(i) + ".png";
        std::string bigBulletRightPath = "Assets/images/BigBulletRight" + std::to_string(i) + ".png";
        imgs_missileDestroyLeft.push_back(rw.loadTexture(bigBulletLeftPath.c_str()));
        imgs_missileDestroyRight.push_back(rw.loadTexture(bigBulletRightPath.c_str()));
    }

    for (int i = 1; i <= 19; i++)
    {
        std::string bombPath = "Assets/images/Bomb" + std::to_string(i) + ".png";
        imgs_bomb.push_back(rw.loadTexture(bombPath.c_str()));
    }
}

void Assets::loadFonts()
{
    font_Test = TTF_OpenFont("Assets/fonts/pixel-bit-advanced.ttf", 30);
    font_Body = TTF_OpenFont("Assets/fonts/TinyPixie2.ttf", 30);
}

void Assets::closeFonts()
{
    TTF_CloseFont(font_Test);
    TTF_CloseFont(font_Body);
}

void Assets::closeTextures()
{

}

Assets::Assets() {}
