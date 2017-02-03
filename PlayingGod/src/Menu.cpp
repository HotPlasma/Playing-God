#include <Menu.h>
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

	CurrentMenu = MainMenu;

	// Sets up font for heads up display
	if (!m_OldSchoolFont.loadFromFile("assets\\fonts\\3x5.TTF"))
	{
		cout << "Error";
	}

	if (CurrentMenu == MainMenu)
	{
		// Set up main menu background
		m_Background.setPosition(0, 0);
		m_Background.setTexture(*m_TexLoader.getTextureIterator(0));
	
		// Sets up game title on main menu
		m_Title.setFont(m_OldSchoolFont);
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

	}

	if (CurrentMenu == NewWorldMenu)
	{
		// Set up main menu background
		m_Background.setPosition(0, 0);
		m_Background.setTexture(*m_TexLoader.getTextureIterator(8));

		// Sets up game title on main menu
		m_Title.setFont(m_OldSchoolFont);
		m_Title.setString("New World Menu");
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

	}

	m_bClicked = false;
	
}

void Menu::TakeMousePos(Vector2f Pos)
{
	// Changes buttons sprites if hovered over
	if (CurrentMenu == MainMenu)
	{
		m_NewWorldButton.CheckHover(Pos);
		m_LoadWorldButton.CheckHover(Pos);
		m_ExitButton.CheckHover(Pos);
	}
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (CurrentMenu == MainMenu)
	{
		target.draw(m_Background);
		target.draw(m_Title);
		target.draw(m_NewWorldButton);
		target.draw(m_LoadWorldButton);
		target.draw(m_ExitButton);
	}
	if (CurrentMenu == NewWorldMenu)
	{
		target.draw(m_Background);
		target.draw(m_Title);
		target.draw(m_NewWorldButton);
		target.draw(m_LoadWorldButton);
		target.draw(m_ExitButton);
	}
}

int Menu::update(float fTimestep)
{
	// Returns value dependent on which button was clicked
	if (CurrentMenu == MainMenu)
	{
		if (m_bClicked)
		{
			if (m_NewWorldButton.isActive())
			{
				return 1;
			}
			else if (m_LoadWorldButton.isActive())
			{
				return 2;
			}
			else if (m_ExitButton.isActive())
			{
				return 3;
			}
			m_bClicked = false;
		}
		return 0;
	}
}

void Menu::Click()
{
	m_bClicked = true;
};
