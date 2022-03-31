#pragma once

//박스 충돌체 컴포넌트 클래스//

class BoxCollider2D
{
private:
	
	float x, y;
	float width, height;

public:
	BoxCollider2D();
	BoxCollider2D(float x, float y, float width, float height);
	virtual ~BoxCollider2D();

	void GetBox(float& x, float& y, float& width, float& height);
	void Translate(float x, float y);


};

