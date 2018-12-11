#include "ViewPort.h"

ViewPort * ViewPort::instance = NULL;

ViewPort::ViewPort()
{
}


ViewPort::~ViewPort()
{
}

ViewPort * ViewPort::GetInstance()
{
	if (instance == NULL)
		instance = new ViewPort();
	return instance;
}

D3DXVECTOR3 ViewPort::ConvertPosInViewPort(D3DXVECTOR3 _realPos)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt); //chuyen ma tran mt ve ma tran dong nhat

	//thiet lap ma tran mt thanh ma tran trung gian
	mt._22 = 1.0f;
	mt._41 = -this->cameraPos.x;
	mt._42 = this->cameraPos.y + 40;

	//hamD3DXVec3Transform se thuc hien nhan position voi ma tran trung gian de ra toa do moi
	//Toa do moi se duoc luu trong vp_pos(viewport position)
	//La toa do da duoc chuyen tu toa do the gioi sang toa do trong viewport
	//Dung toa do nay de ve
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &_realPos, &mt);

	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
}

void ViewPort::SetCameraPos(D3DXVECTOR3 _camPos)
{
	cameraPos = _camPos;
}
