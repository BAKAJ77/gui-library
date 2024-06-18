#include <components/radio_group.h>

namespace GUILib
{
	RadioGroup::RadioGroup(int spacing) :
		m_spacing(spacing), m_currentSelected(-1)
	{
		this->InitializeComponent();
	}

	RadioGroup::~RadioGroup()
	{
		for (auto& option : m_options)
		{
			delete option.button;
			delete option.text;
		}
	}

	void RadioGroup::InitializeComponent() { m_position = { 0, 0 }; }

	void RadioGroup::CalculatePosition(RadioButtonOption& option, int index)
	{
		if (index > 0)
		{
			const RadioButtonOption& lastOption = m_options[(size_t)index - 1];

			option.button->SetPosition({
				lastOption.text->GetPosition().x + lastOption.text->GetSize().x + (option.button->GetDiameter() / 2) + m_spacing,
				m_position.y });
		}
		else
			option.button->SetPosition({ m_position.x + (option.button->GetDiameter() / 2), m_position.y });

		option.text->SetPosition({ option.button->GetPosition().x + (option.button->GetDiameter() / 2) + 10,
				m_position.y + (option.text->GetSize().y / 2) });
	}

	void RadioGroup::AddOption(RadioButtonOption option)
	{
		// Make sure there isn't already an existing option with the same value ID
		for (const auto& existingOption : m_options)
		{
			if (existingOption.valueID == option.valueID)
				return;
		}

		// Make sure that the value ID given is larger than 0
		if (option.valueID < 0)
			return;

		// Add the new option to the group
		this->CalculatePosition(option, m_options.size());
		m_options.emplace_back(option);
	}

	void RadioGroup::RemoveOption(int valueID)
	{
		for (auto it = m_options.begin(); it != m_options.end(); it++)
		{
			if (it->valueID == valueID)
			{
				m_options.erase(it);
				break;
			}
		}
	}

	void RadioGroup::SetSelectedOption(int valueID)
	{
		if (valueID < 0) // If valueID is less than 0 then set no option as current selected
		{
			m_currentSelected = -1;
			for (const auto& option : m_options)
				option.button->SetSelected(false);
		}
		else
		{
			for (const auto& option : m_options)
			{
				if (option.valueID == valueID)
				{
					option.button->SetSelected(true);
					m_currentSelected = valueID;
					break;
				}
				else
				{
					option.button->SetSelected(false);
					m_currentSelected = -1;
				}
			}
		}
	}

	void RadioGroup::SetPosition(glm::ivec2 pos) 
	{ 
		m_position = pos; 

		// Update the positions of all radio button options in the group
		for (int i = 0; i < m_options.size(); i++)
			this->CalculatePosition(m_options[i], i);
	}

	void RadioGroup::Update(float deltaTime)
	{
		// Check if any radio buttons were selected
		bool optionSelected = false;
		for (auto& option : m_options)
		{
			option.button->Update(deltaTime);
			if (option.button->WasClicked())
			{
				option.button->SetSelected(true);
				m_currentSelected = option.valueID;
				optionSelected = true;
				break;
			}
		}

		// If a radio button was selected, unselect any other which was previously selected
		if (optionSelected)
		{
			for (auto& option : m_options)
			{
				if (option.valueID != m_currentSelected)
					option.button->SetSelected(false);
			}
		}
	}

	void RadioGroup::Render(const Viewport& viewport) const
	{
		for (const auto& option : m_options)
		{
			option.button->Render(viewport);
			option.text->Render(viewport);
		}
	}

	const int& RadioGroup::GetSelectedOption() const { return m_currentSelected; }

	const glm::ivec2& RadioGroup::GetPosition() const { return m_position; }
}
