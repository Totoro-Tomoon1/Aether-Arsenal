#include "pch.h"
#include "main.h"
#include "GameManager.h"

int main()
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	srand(time(NULL)); //max only

	GameManager::GetInstance()->PlayGame();

	

	return 0;
}
