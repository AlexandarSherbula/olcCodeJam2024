#include "Camera.h"
#include "Game.h"

Camera::Camera()
{
}

void Camera::Create()
{
	position = { 0.0f, 0.0f };
    focalPoint = { game->ScreenWidth() / 2.0f, game->ScreenHeight() / 2.0f };

    mLeftBorder   = focalPoint.x - 8.0f;
    mRightBorder  = focalPoint.x + 8.0f;
    mTopBorder    = focalPoint.y - 32.0f;
    mBottomBorder = focalPoint.y + 32.0f;
}

void Camera::Update()
{
    olc::vf2d localOffset = game->player.position - (focalPoint + offset);

    if (game->player.position.x < mLeftBorder)
        offset.x = (game->player.position.x + 8.0f) - focalPoint.x;
    else if (game->player.position.x > mRightBorder)
        offset.x = (game->player.position.x - 8.0f) - focalPoint.x;

    offset.y = game->player.position.y - focalPoint.y;

    if (game->player.position.x < 0) game->player.position.x = 0;
    if (game->player.position.x > game->map.size.x - 1) game->player.position.x = game->map.size.x;

    if (offset.x < 0) offset.x = 0;
    if (offset.x > game->map.size.x - game->ScreenWidth()) offset.x = game->map.size.x - game->ScreenWidth();
    if (offset.y < 0) offset.y = 0;
    if (offset.y > game->map.size.y - game->ScreenHeight()) offset.y = game->map.size.y - game->ScreenHeight();

    mLeftBorder = focalPoint.x - 8.0f + offset.x;
    mRightBorder = focalPoint.x + 8.0f + offset.x;
    mTopBorder = focalPoint.y - 32.0f + offset.y;
    mBottomBorder = focalPoint.y + 32.0f + offset.y;

}

void Camera::DrawBorders()
{
    game->FillRectDecal(olc::vf2d(mLeftBorder, mTopBorder) - offset,    olc::vf2d(16.0f, 1.0f));
    game->FillRectDecal(olc::vf2d(mLeftBorder, mTopBorder) - offset,    olc::vf2d(1.0f, 64.0f));
    game->FillRectDecal(olc::vf2d(mRightBorder, mTopBorder) - offset,   olc::vf2d(1.0f, 64.0f));
    game->FillRectDecal(olc::vf2d(mLeftBorder,  mBottomBorder) - offset, olc::vf2d(17.0f, 1.0f));

    game->FillRectDecal(olc::vf2d(mLeftBorder, mTopBorder + 32.0f) - offset, olc::vf2d(17.0f, 1.0f), olc::GREEN);
}
