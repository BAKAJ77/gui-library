#ifndef RADIO_GROUP_H
#define RADIO_GROUP_H

#include <components/radio_button.h>
#include <components/label.h>

namespace GUILib
{
	class LIB_DECLSPEC RadioGroup : public Component
	{
	public:
		/**
		* @brief Struct that contains data on a radio button option
		*/
		struct RadioButtonOption
		{
			RadioButton* button;
			Label* text;
			int valueID = -1;
		};

		/**
		* @brief This is the default class constructor.
		* @param[in] spacing - The amount of spacing between radio button options.
		*/
		RadioGroup(int spacing = 30);

		~RadioGroup();

		/** 
		* @brief Adds the radio button option to the group.
		* @param[in] option - The new option to be added to the group.
		*/
		void AddOption(RadioButtonOption option);

		/** 
		* @brief Removes the radio button assigned with the value ID given.
		* @param[in] valueID - The value ID of the radio button to remove.
		*/
		void RemoveOption(int valueID);

		/** 
		* @brief Sets the radio button option assigned with the value ID given as current selected.
		* @param[in] valueID - The value ID of the radio button option to be set as selected. If the valueID given is < 0
		* or no radio button option was found with the given value ID, then current selected will be set to null, no option will be current
		* selected.
		*/
		void SetSelectedOption(int valueID);

		/**
		* @brief Sets the current position of the radio group component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Updates the logic of the radio group component.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the radio group component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/** 
		* @brief Returns the value ID of the current selected radio button option.
		* @return The value ID of the selected radio button option.
		*/
		const int& GetSelectedOption() const;

		/**
		* @brief Returns the current position of the radio group component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;
	private:
		/**
		* @brief Initialises the radio group component.
		*/
		void InitializeComponent() override;

		/** 
		* @brief Calculates and sets the position where an option should be.
		* @param[in] option - The option to have its position calculated then updated.
		* @param[in] index - The index of the option in the vector array.
		*/
		void CalculatePosition(RadioButtonOption& option, int index);
	private:
		glm::ivec2 m_position;
		std::vector<RadioButtonOption> m_options;
		int m_spacing, m_currentSelected;
	};
}

#endif
