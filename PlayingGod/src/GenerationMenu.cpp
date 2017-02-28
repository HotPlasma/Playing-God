#include <GenerationMenu.h>


GenerationMenu::GenerationMenu(int WindowWidth, int WindowHeight)
{
	// Load in all textures needed for main menu
	m_TexLoader.setBaseDirectory("assets\\UI\\");
	m_TexLoader.load(std::vector<std::string>{
		"CreationBackground.png",
			"Cancel.png",
			"CancelHover.png",
			"Create.png",
			"CreateHover.png"
	});

	m_TextBox_WorldName = new TextBox(710, 70);

	// Set up main menu background
	m_Background.setPosition(0, 0);
	m_Background.setTexture(*m_TexLoader.getTextureIterator(0));

	//WORLD NAME
	// Sets up world name label on main menu
	m_WorldName.setFont(m_BlockFont);
	m_WorldName.setString("World Name:");
	m_WorldName.setCharacterSize(50);

	// Centre text
	sf::FloatRect TempRect = m_WorldName.getLocalBounds();
	m_WorldName.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_WorldName.setPosition(sf::Vector2f(WindowWidth / 2.0f - 300, WindowHeight / 9.0f));

	//WORLD SIZE
	// Sets up world size label on main menu
	m_WorldSize.setFont(m_BlockFont);
	m_WorldSize.setString("World Size:");
	m_WorldSize.setCharacterSize(50);

	// Centre text
	TempRect = m_WorldSize.getLocalBounds();
	m_WorldSize.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_WorldSize.setPosition(sf::Vector2f(WindowWidth / 2.0f - 500, 300));

	//TEMPERATURE
	// Sets up world size label on main menu
	m_Temperature.setFont(m_BlockFont);
	m_Temperature.setString("Temperature:");
	m_Temperature.setCharacterSize(50);

	// Centre text
	TempRect = m_Temperature.getLocalBounds();
	m_Temperature.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Temperature.setPosition(sf::Vector2f(WindowWidth / 2.0f - 500, 400));

	//MOUNTAINS
	m_Mountainous.setFont(m_BlockFont);
	m_Mountainous.setString("Mountainous:");
	m_Mountainous.setCharacterSize(50);

	// Centre text
	TempRect = m_Mountainous.getLocalBounds();
	m_Mountainous.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Mountainous.setPosition(sf::Vector2f(WindowWidth / 2.0f - 500, 500));
	// Sets up main menu buttons positions and starting textures

	//CIVILISATION
	m_Civilisation.setFont(m_BlockFont);
	m_Civilisation.setString("Mountainous:");
	m_Civilisation.setCharacterSize(50);

	// Centre text
	TempRect = m_Civilisation.getLocalBounds();
	m_Civilisation.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Civilisation.setPosition(sf::Vector2f(WindowWidth / 2.0f + 200, 300));
	// Sets up main menu buttons positions and starting textures

	//SKYBOX
	m_SkyBox.setFont(m_BlockFont);
	m_SkyBox.setString("Time of Day:");
	m_SkyBox.setCharacterSize(50);

	// Centre text
	TempRect = m_SkyBox.getLocalBounds();
	m_SkyBox.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_SkyBox.setPosition(sf::Vector2f(WindowWidth / 2.0f + 200, 400));

	//TREE DENSITY
	m_TreeDensity.setFont(m_BlockFont);
	m_TreeDensity.setString("Tree Density:");
	m_TreeDensity.setCharacterSize(50);

	// Centre text
	TempRect = m_TreeDensity.getLocalBounds();
	m_TreeDensity.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_TreeDensity.setPosition(sf::Vector2f(WindowWidth / 2.0f + 200, 500));



	m_Cancel.SetProperties( WindowWidth / 12 , WindowHeight / 1.2, 1, &m_TexLoader);

	m_Create.SetProperties(WindowWidth / 1.5 , WindowHeight / 1.2, 3, &m_TexLoader);



	m_bClicked = false;

}

void GenerationMenu::TakeMousePos(Vector2f Pos)
{
	// Changes buttons sprites if hovered over

	m_Cancel.CheckHover(Pos);
	m_Create.CheckHover(Pos);

}

void GenerationMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	target.draw(m_Background);
	target.draw(m_Cancel);
	target.draw(m_Create);
	target.draw(m_WorldName);
	target.draw(m_WorldSize);
	target.draw(m_Temperature);
	target.draw(m_Mountainous);
	target.draw(m_Misc);
	target.draw(m_Civilisation);
	target.draw(m_SkyBox);
	target.draw(m_TreeDensity);
	target.draw(*m_TextBox_WorldName);
}

int GenerationMenu::update(float fTimestep)
{
	// Returns value dependent on which button was clicked

	if (m_bClicked)
	{
		if (m_Create.isActive())
		{
			WhichState = Cancel;
		}
		else if (m_Cancel.isActive())
		{
			WhichState = Create;
		}
		m_bClicked = false;
		return WhichState;
	}
	return WhichState = None;

}

int GenerationMenu::ReturnButtonClicked()
{
	return WhichState;
}