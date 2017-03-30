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
			"CreateHover.png",
			"DropBox.png",
			"Extention.png"
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

	// Worldsize DropBox
	m_WorldSizeOptions.SetProperties(460, 260, 5, &m_TexLoader, vector<string>{"Small", "Medium", "Large"});

	//m_DropDownMenus.push_back(m_WorldSizeOptions);

	//TEMPERATURE
	// Sets up world size label on main menu
	m_Climate.setFont(m_BlockFont);
	m_Climate.setString("Climate:");
	m_Climate.setCharacterSize(50);

	// Centre text
	TempRect = m_Climate.getLocalBounds();
	m_Climate.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Climate.setPosition(sf::Vector2f(WindowWidth / 2.0f - 500, 400));

	// Climate DropBox
	m_ClimateOptions.SetProperties(460, 360, 5, &m_TexLoader, vector<string>{"Cold", "Warm", "Hot"});

	//m_DropDownMenus.push_back(m_ClimateOptions);

	//MOUNTAINS
	m_Mountainous.setFont(m_BlockFont);
	m_Mountainous.setString("Mountainous:");
	m_Mountainous.setCharacterSize(50);

	// Centre text
	TempRect = m_Mountainous.getLocalBounds();
	m_Mountainous.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Mountainous.setPosition(sf::Vector2f(WindowWidth / 2.0f - 500, 500));
	// Sets up main menu buttons positions and starting textures

	// Mountains DropBox
	m_MountainousOptions.SetProperties(460, 460, 5, &m_TexLoader, vector<string>{"None", "Slightly", "Heavily"});

	//CIVILISATION
	m_Civilisation.setFont(m_BlockFont);
	m_Civilisation.setString("Civilisation:");
	m_Civilisation.setCharacterSize(50);

	// Centre text
	TempRect = m_Civilisation.getLocalBounds();
	m_Civilisation.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_Civilisation.setPosition(sf::Vector2f(WindowWidth / 2.0f + 200, 300));
	// Sets up main menu buttons positions and starting textures

	// Civilization DropBox
	m_CivilisationOptions.SetProperties(1200, 260, 5, &m_TexLoader, vector<string>{"None", "Remains", "Mass Remains"});

	//SKYBOX
	m_SkyBox.setFont(m_BlockFont);
	m_SkyBox.setString("Time of Day:");
	m_SkyBox.setCharacterSize(50);

	// Centre text
	TempRect = m_SkyBox.getLocalBounds();
	m_SkyBox.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_SkyBox.setPosition(sf::Vector2f(WindowWidth / 2.0f + 200, 400));

	// Skybox DropBox
	m_SkyBoxOptions.SetProperties(1200, 360, 5, &m_TexLoader, vector<string>{"Day", "Sun Set", "Night"});

	//TREE DENSITY
	m_FloraDensity.setFont(m_BlockFont);
	m_FloraDensity.setString("Flora Density:");
	m_FloraDensity.setCharacterSize(50);

	// Centre text
	TempRect = m_FloraDensity.getLocalBounds();
	m_FloraDensity.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_FloraDensity.setPosition(sf::Vector2f(WindowWidth / 2.0f + 200, 500));

	// Flora Density DropBox
	m_FloraDensityOptions.SetProperties(1200, 460, 5, &m_TexLoader, vector<string>{"None", "Low", "Medium", "High"});

	m_Cancel.SetProperties( WindowWidth / 12 , WindowHeight / 1.2, 1, &m_TexLoader);

	m_Create.SetProperties(WindowWidth / 1.5 , WindowHeight / 1.2, 3, &m_TexLoader);

	// Text to appear while loading
	m_LoadingText.setFont(m_BlockFont);
	m_LoadingText.setString("Creating large worlds takes time. Please be patient...");
	m_LoadingText.setCharacterSize(50);
	TempRect = m_LoadingText.getLocalBounds();
	m_LoadingText.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_LoadingText.setPosition(sf::Vector2f(WindowWidth / 2.0f, 680));
	m_LoadingText.setFillColor(sf::Color::Yellow);

	m_bClicked = false;
	m_bMenuOpen = false;
	// Fill vector will all drop down boxes.
	m_DropDownMenus.insert(m_DropDownMenus.end(), { m_MountainousOptions, m_ClimateOptions, m_WorldSizeOptions, m_FloraDensityOptions, m_SkyBoxOptions, m_CivilisationOptions });
	/*	m_MiscOptions*/
}

void GenerationMenu::TakeMousePos(Vector2f Pos)
{
	// Changes buttons sprites if hovered over

	m_Cancel.CheckHover(Pos);
	m_Create.CheckHover(Pos);
	for (int i = 0; i < m_DropDownMenus.size(); i++)
	{
		m_DropDownMenus.at(i).CheckHover(Pos);
		if (m_DropDownMenus.at(i).isOpen())
		{
			m_DropDownMenus.at(i).CheckHoverDropDownOptions(Pos);
		}
	}
	/*if (m_ClimateOptions.isOpen())
	{
		m_ClimateOptions.CheckHoverDropDownOptions(Pos);
	}*/
}

void GenerationMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	
	target.draw(m_Background);
	target.draw(m_Cancel);
	target.draw(m_Create);
	target.draw(m_WorldName);
	target.draw(m_WorldSize);
	target.draw(m_Climate);
	target.draw(m_Mountainous);
	target.draw(m_Civilisation);
	target.draw(m_SkyBox);
	target.draw(m_FloraDensity);
	target.draw(*m_TextBox_WorldName);
	target.draw(m_LoadingText);
	for (DropDownMenu Menus : m_DropDownMenus)
	{
		target.draw(Menus);
	}
	
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

		for (int i = 0; i < m_DropDownMenus.size(); i++)
		{
			if (m_DropDownMenus.at(i).isActive())
			{
				if (!m_bMenuOpen)
				{
					m_DropDownMenus.at(i).ToggleOpen();
					m_bMenuOpen = true;
				}

			}
			else
			{
				m_DropDownMenus.at(i).CloseMenu();
				m_bMenuOpen = false;
			}

			/*if (!m_DropDownMenus.at(i).isOpen())
			{
				for (auto Menus : m_DropDownMenus)
				{
					Menus.CloseMenu();
				}
			}*/
		}
			
		//}
		// Toggles World Size Drop Down Menu
		//else if (m_WorldSizeOptions.isActive())
		//{
		//	m_WorldSizeOptions.ToggleOpen();
		//}
		//else if (m_ClimateOptions.isActive())
		//{
		//	m_ClimateOptions.ToggleOpen();
		//}
		
		m_bClicked = false;
		return WhichState;
	}
	return WhichState = None;

}

int GenerationMenu::ReturnButtonClicked()
{
	return WhichState;
}