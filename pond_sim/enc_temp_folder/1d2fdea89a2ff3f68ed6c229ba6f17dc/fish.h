#pragma once

#include <string>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

class Fish {
private:

	std::string name = "";
	float x = 0.f;            
	float y = 0.f;
	float direction = 0.f;
	float speed = 0.f;        
	int size = 0;             
	std::vector<int> color = {255, 0, 0};

	float cruiseSpeed = 0.f;  
	float maxTurnRate = 0.f;  
	float retargetTimer = 0.f;
	sf::Vector2f target = {0.f, 0.f};
	bool hasTarget = false;

	std::vector<sf::Vector2f> spine = {};
	std::vector<sf::Vector2f> bodyPoints = {};
	float wigglePhase = 0.f;

	struct Spot {
		float t;       
		float lateral; 
		float radius;  
		float stretch;
	};
	std::vector<Spot> spots = {};
	sf::Color spotColor = sf::Color(225, 70, 35);

	// Per-fish size multipliers (around 1.0) so every part of each koi is slightly different.
	struct Proportions {
		float body = 1.f;  // also sets the head width, which matches the widest part of the body
		float tailBase = 1.f;
		float tailFlare = 1.f;
		float tailTip = 1.f;
		float bigFin = 1.f;
		float smallFin = 1.f;
		float eye = 1.f;
	};
	Proportions shape;

	static constexpr int spineCount = 20;

	static constexpr float partVariation = 0.12f;  // how much each part can differ: 0.12 = up to 12% bigger or smaller
	static constexpr float noSpotChance = 0.0f;   // chance a koi has no spots at all

	static constexpr float wiggleAmount = 0.04f;   // how far the tail swings side to side, as a fraction of length
	static constexpr float minWanderTime = 10.f;   // seconds before a fish gives up on a destination and picks another
	static constexpr float maxWanderTime = 20.f;
	static constexpr float wallMargin = 0.6f;      // how close to the wall a fish aims, as a fraction of its length

	static constexpr float bodyEnd = 0.68f;        
	static constexpr float maxBodyWidth = 0.105f;  
	static constexpr float tailBaseWidth = 0.028f; 
	static constexpr float tailFlareWidth = 0.07f; 
	static constexpr float tailTipWidth = 0.11f;   
	static constexpr float eyeSize = 5.f;          // eye radius in pixels, the same for every fish size
	static constexpr float pupilSize = 0.5f;      
	static constexpr float bigFinSize = 0.16f;     
	static constexpr float smallFinSize = 0.10f;   

	void initBody();
	void pickTarget(const sf::FloatRect& bounds);
	float halfWidthAt(float t) const;

public:

	Fish();
	Fish(int xCoordinate, int yCoordinate, std::string fishName, int fishSize, std::vector<int> fishColor);

	void update(float deltaTime, const sf::FloatRect& bounds);
	void draw(float deltaTime, sf::RenderWindow& surface);

	float getX() const;
	float getY() const;
	float getDirection() const;
	float getSpeed() const;
	int getSize() const;
	std::vector<int> getColor() const;
	std::string getName() const;

};
