#include <MainMenu.h>
#include <Button.h>

Menu::Menu(int WindowWidth, int WindowHeight)
{
	// Load in all textures needed for main menu
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"MenuBackground3.png",
			"NewWorld.png",
			"NewWorldHover.png",
			"LoadWorld.png",
			"LoadWorldHover.png",
			"Exit.png",
			"ExitHover.png",
			"MenuBackground2.png"
	});

	//// Sets up font for heads up display
	//if (!m_BlockFont.loadFromFile("assets\\fonts\\3x5.TTF"))
	//{
	//	cout << "Error";
	//}

	
		// Set up main menu background
		m_Background.setPosition(0, 0);
		m_Background.setTexture(*m_TexLoader.getTextureIterator(0));
	
		// Sets up game title on main menu
		m_Title.setFont(m_BlockFont);
		m_Title.setString("World Creation Menu");
		m_Title.setCharacterSize(100);

		// Centre text
		sf::FloatRect TitleRect = m_Title.getLocalBounds();
		m_Title.setOrigin(TitleRect.left + TitleRect.width / 2.0f, TitleRect.top + TitleRect.height / 2.0f);
		m_Title.setPosition(sf::Vector2f(WindowWidth / 2.0f, WindowHeight / 8.0f));
		//m_Title.setColor(Color::White);

		// Sets up main menu buttons positions and starting textures
		m_NewWorldButton.SetProperties(WindowWidth / 2 - 200, 250, 1, &m_TexLoader);

		m_LoadWorldButton.SetProperties(WindowWidth / 2 - 200, 350, 3, &m_TexLoader);

		m_ExitButton.SetProperties(WindowWidth / 2 - 200, 550, 5, &m_TexLoader);


	m_bClicked = false;
	
}

void Menu::TakeMousePos(Vector2f Pos)
{
	// Changes buttons sprites if hovered over
	
		m_NewWorldButton.CheckHover(Pos);
		m_LoadWorldButton.CheckHover(Pos);
		m_ExitButton.CheckHover(Pos);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	
		target.draw(m_Background);
		target.draw(m_Title);
		target.draw(m_NewWorldButton);
		target.draw(m_LoadWorldButton);
		target.draw(m_ExitButton);
}

int Menu::update(float fTimestep)
{
	// Returns value dependent on which button was clicked
	
		if (m_bClicked) // If clicked
		{
			if (m_NewWorldButton.isActive()) // New World button clicked
			{
				WhichState = NewWorld;
			}
			else if (m_LoadWorldButton.isActive()) // Load world button clicked
			{
				WhichState = LoadWorld;
			}
			else if (m_ExitButton.isActive()) // Exit button clicked
			{
				WhichState = ExitMenu;
			}
			m_bClicked = false; // "Unclick" button
			return WhichState; // Return which button was clicked
		}
		return WhichState = None; // If no button clicked return none
	
}

int Menu::ReturnButtonClicked()
{
	return WhichState;
}



//void Menu::Click()
//{
//	m_bClicked = true;
//};
