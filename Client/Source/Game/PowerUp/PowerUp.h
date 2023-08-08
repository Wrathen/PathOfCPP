#pragma once
#include "../../UI/UIElement.h"
#include "../../Components/TextRenderer.h"

typedef void (*FuncOnPowerUp)();
class PowerUp: public UIElement {
public:
	std::string text;
	std::string description;

	// Lambda function
	FuncOnPowerUp OnPowerUp;

	TextRenderer text_name;
	TextRenderer text_description;

	static const int width = 550; // 320
	static const int height = 700; // 540

	PowerUp(std::string _text, std::string _description, FuncOnPowerUp funcOnPowerUp);

	static PowerUp* GetRandom();
	static void InitAllPowerUps();

	void Start() override;
	void Update() override {};
	void Render() override;

	void OnDelete() override {}

	bool OnClick() override;
	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};