#include <LoadingMenu.h>


LoadingMenu::LoadingMenu(int WindowWidth, int WindowHeight)
{
	// Load in all textures needed for main menu
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"CreationBackground.png",
			"Cancel.png",
			"CancelHover.png",
			"Load.png",
			"LoadHover.png"
	});

	// Set up main menu background
	m_Background.setPosition(0, 0);
	m_Background.setTexture(*m_TexLoader.getTextureIterator(0));

	// Instructions
	m_Instructions.setFont(m_BlockFont);
	m_Instructions.setString("Type the name of the world you wish to load");
	m_Instructions.setCharacterSize(40);

	// Centre text
	sf::FloatRect TempRect = m_Instructions.getLocalBounds();
	m_Instructions.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Instructions.setPosition(sf::Vector2f(WindowWidth / 2.0f , WindowHeight / 9.0f));

	m_TextBox_WorldName = new TextBox(m_Instructions.getPosition().x - 200, WindowHeight / 2.0f);

	m_Cancel.SetProperties(WindowWidth / 12, WindowHeight / 1.2, 1, &m_TexLoader);

	m_Load.SetProperties(WindowWidth / 1.5, WindowHeight / 1.2, 3, &m_TexLoader);

}

void LoadingMenu::TakeMousePos(Vector2f Pos)
{
	// Changes buttons sprites if hovered over
	m_Cancel.CheckHover(Pos);
	m_Load.CheckHover(Pos);
	
}

void LoadingMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_Background);
	target.draw(m_Cancel);
	target.draw(m_Load);
	target.draw(m_Instructions);
	target.draw(*m_TextBox_WorldName);
	target.draw(m_LoadingText);
}

int LoadingMenu::update(float fTimestep)
{
	// Returns value dependent on which button was clicked
	if (m_bClicked)
	{
		if (m_Load.isActive())
		{
			WhichState = Cancel;
		}
		else if (m_Cancel.isActive())
		{
			WhichState = Load;
		}

		m_bClicked = false;
		return WhichState;
	}

	return WhichState = None;
}

int LoadingMenu::ReturnButtonClicked()
{
	return WhichState;
}