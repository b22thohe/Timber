#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

const float TREE_H_POS = 810;
const float TREE_V_POS = 0;
const float BEE_H_POS = 0;
const float BEE_V_POS = 800;
const float CLOUD1_V_POS = 0;
const float CLOUD2_V_POS = 250;
const float CLOUD3_V_POS = 500;

// This is where the game starts from int main()
int main() {
	// Create a video mode object
	VideoMode vm(1920, 1080);
	
	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!", Style::Fullscreen);
	
	// Create texture to hold a graphic
	Texture textureBackground;
	
	// Load graphic into texture
	textureBackground.loadFromFile("graphics/background.png");
	
	// Create a sprite
	Sprite spriteBackground;
	
	// Attach texture to sprite
	spriteBackground.setTexture(textureBackground);
	
	// Set sprite to cover the screen
	spriteBackground.setPosition(0, 0);
	
	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(TREE_H_POS, TREE_V_POS);
	
	// Prepare the bee sprite
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(BEE_H_POS, BEE_V_POS);
	
	// Set bee activity
	bool beeActive = false;
	
	// Set bee movement speed
	float beeSpeed = 0.0f;

	// Make some clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	// Position clouds left on screen at different heights
	spriteCloud1.setPosition(0, CLOUD1_V_POS);
	spriteCloud2.setPosition(0, CLOUD2_V_POS);
	spriteCloud3.setPosition(0, CLOUD3_V_POS);

	// Set cloud activity
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// Set cloud movement speed
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Time control variables
	Clock clock;

	// Setup paus function
	bool isPaused = true;
	bool pausedAtStart = true;
	bool paused = true;

	// Declare some text properties
	int score = 0;

	Text messageText;
	Text scoreText;
	Text pauseMessageText;

	// Set the font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Make outputs use the font
	messageText.setFont(font);
	scoreText.setFont(font);
	pauseMessageText.setFont(font);

	// Set output texts
	messageText.setString("Press <SPACE> to start!");
	scoreText.setString("Score: 0");
	pauseMessageText.setString("Game is paused! Press <SPACE> to resume!");

	// Set font size
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	pauseMessageText.setCharacterSize(75);

	// Set text color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	pauseMessageText.setFillColor(Color::Red);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	FloatRect pauseTextRect = pauseMessageText.getLocalBounds();
	pauseMessageText.setOrigin(pauseTextRect.left +
		pauseTextRect.width / 2.0f,
		pauseTextRect.top +
		pauseTextRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	pauseMessageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	while (window.isOpen()) {
		/* 1. Handle Events (Better for Toggles) */
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			// Check for a single key press
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					isPaused = !isPaused;

					pausedAtStart = false;

					if (!pausedAtStart)
					{
						paused = !paused;
					}
				}
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
			}
		}

		if (!isPaused)
		{
			/* Update scene */

			// Measure time
			Time dt = clock.restart();

			// Manage the bee
			if (!beeActive)
			{
				// The speed of the bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// The altitude of the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			} else
			{
				// Move the bee
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Check if bee has reached left side of screen
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up to be a new bee next frame
					beeActive = false;
				}
			}

			// Manage the clouds
			// Cloud 1
			if (!cloud1Active)
			{
				// Speed of the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// Altitude of the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			} else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				// Check if cloud has reached right side of screen
				if (spriteCloud1.getPosition().x > 1920)
				{
					// Set it up to be a new cloud next frame
					cloud1Active = false;
				}
			}

			// Cloud 2
			if (!cloud2Active)
			{
				// Speed of the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				// Altitude of the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 150);
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			} else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);

				// Check if cloud has reached right side of screen
				if (spriteCloud2.getPosition().x > 1920)
				{
					// Set it up to be a new cloud next frame
					cloud2Active = false;
				}
			}

			// Cloud 3
			if (!cloud3Active)
			{
				// Speed of the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				// Altitude of the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 150);
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			} else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);

				// Check if cloud has reached right side of screen
				if (spriteCloud3.getPosition().x > 1920)
				{
					// Set it up to be a new cloud next frame
					cloud3Active = false;
				}
			}
		} else
		{
			clock.restart();
		}

		// Update score
		std::stringstream ss;
		ss << "Score: " << score;
		scoreText.setString(ss.str());

		/* Draw scene */

		// Clear everything from last frame
		window.clear();

		// Draw game scene
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		window.draw(scoreText);

		if (pausedAtStart)
		{
			window.draw(messageText);
		}

		if (paused && !pausedAtStart)
		{
			window.draw(pauseMessageText);
		}

		// Show everything we just drew
		window.display();
	}
	
	return 0;
}
