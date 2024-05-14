#pragma once
#define KEYBOARD_MAX 256

namespace Input
{
	class InputSystem;
	extern InputSystem* inputManager;

	class InputSystem
	{
	private:
		BYTE _byKeyPrev[KEYBOARD_MAX];		// ���� Ű�� ����
		BYTE _byKeyCurr[KEYBOARD_MAX];		// ���� Ű�� ����
		BYTE _byKeyTurnDn[KEYBOARD_MAX];	// Down�� Ű�� ����
		BYTE _byKeyTurnUp[KEYBOARD_MAX];   // Up �� Ű�� ����

		HWND _hWnd;
		int _width;
		int _height;

		POINT _mouseClient;

		static InputSystem* _sInstance;

		InputSystem() {};
		~InputSystem();
	public:

		/**
	 * @brief ��ǲ �ý��� �ʱ�ȭ
	 */
		void InitInput();
		void ReleaseInput();
		/**
	 * @brief ��ǲ ���� ������Ʈ
	 */
		void Update();

		/**
	 * @brief Ű�� �ѹ� ���ȴ°��� �Ǵ�
	 * @param vk �Ǻ��� Ű
	 * @return
	 */
		BOOL IsTurnDn(BYTE vk);

		/**
	 * @brief Ű�� �ѹ� �����°��� �Ǵ�
	 * @param vk �Ǻ��� Ű
	 * @return
	 */
		BOOL IsTurnUp(BYTE vk);

		/**
	 * @brief Ű�� ���� �ִ°��� �Ǵ�
	 * @param vk �Ǻ��� Ű
	 * @return
	 */
		BOOL IsCurrDn(BYTE vk);

		/**
	 * @brief Ű�� ������ �ִ°��� �Ǵ�
	 * @param vk �Ǻ��� Ű
	 * @return
	 */
		BOOL IsCurrUp(BYTE vk);

		/**
	 * @brief ���� ���콺 ��ġ�� ��ȯ��
	 * @return ���� ���콺 ��ġ
	 */
		POINT GetMouseClient();

		static InputSystem* GetInstance();
		static void DestroyInsatance();
	};
}

