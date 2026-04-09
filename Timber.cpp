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

enum class State { PAUSED, PLAYING, GAME_OVER, START_SCREEN };

void centerText(Text& text, Vector2f position) {
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
				   textRect.top + textRect.height / 2.0f);
	text.setPosition(position);
}

// Function for handling clouds
void updateCloud(Sprite& cloud, float& speed, bool& active, float dt, int screenWidth)
{
	if (!active) {
		speed = (rand() % 200);
		float height = (rand() % 150);
		cloud.setPosition(-200, height);
		active = true;
	} else {
		cloud.setPosition(cloud.getPosition().x + (speed * dt), cloud.getPosition().y);
		if (cloud.getPosition().x > screenWidth) {
			active = false;
		}
	}
}

// This is where the game starts from int main()
int main() {
	srand((int)time(0));

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

	// Timer bar
	RectangleShape timerBar;
	float timerBarStartWidth = 400;
	float timerBarHeight = 80;
	timerBar.setSize(Vector2f(timerBarStartWidth, timerBarHeight));
	timerBar.setFillColor(Color::Red);
	timerBar.setPosition((1920 / 2) - timerBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timerRemaining = 6.0f;
	float timerBarWidthPerSecond = timerBarStartWidth / timerRemaining;

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

	State gameState = State::START_SCREEN;

	while (window.isOpen()) {
		/* 1. Handle Events (Better for Toggles) */
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			// Check for a single key press
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					switch (gameState)
					{
						case State::START_SCREEN:
							// Move from start state to begin the game
							gameState = State::PLAYING;
							break;

						case State::PLAYING:
							// Move from playing to pause
							gameState = State::PAUSED;
							break;

						case State::PAUSED:
							// Move from paused to playing
							gameState = State::PLAYING;
							break;

						case State::GAME_OVER:
							// 1. Reset game variables
							score = 0;
							timerRemaining = 6.0f;

							// 2. Reset scene objects so they spawn fresh
							beeActive = false;
							cloud1Active = false;
							cloud2Active = false;
							cloud3Active = false;

							// 3. Change state to start playing again immediately
							gameState = State::PLAYING;
							break;
					}
				}
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == Keyboard::Enter)
				{
					gameState = State::START_SCREEN;
					messageText.setString("Press <SPACE> to start!");
					centerText(messageText, Vector2f(1920 / 2.0f, 1080 / 2.0f));

					// 3. Reset game variables
					score = 0;
					timerRemaining = 6.0f;
					beeActive = false;
					cloud1Active = false;
					cloud2Active = false;
					cloud3Active = false;
				}
			}
		}

		/* Update scene */

		if (gameState == State::PLAYING)
		{
				// Measure time
			Time dt = clock.restart();

			// Subtract from time remaining
			timerRemaining -= dt.asSeconds();
			// Set size of timer bar
			timerBar.setSize(Vector2f(timerBarWidthPerSecond *
				timerRemaining, timerBarHeight));

			if (timerRemaining <= 0.0f)
			{
				// Pause the game
				gameState = State::GAME_OVER;
				// Message to the player
				messageText.setString("Press <SPACE> to start!");
				centerText(messageText, Vector2f(1920 / 2.0f, 1080 / 2.0f));
			}

			// Manage the bee
			if (!beeActive)
			{
				// The speed of the bee
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
			updateCloud(spriteCloud1, cloud1Speed, cloud1Active, dt.asSeconds(), 1920);
			updateCloud(spriteCloud2, cloud2Speed, cloud2Active, dt.asSeconds(), 1920);
			updateCloud(spriteCloud3, cloud3Speed, cloud3Active, dt.asSeconds(), 1920);
		}
		else
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
		window.draw(timerBar);

		if (gameState == State::GAME_OVER || gameState == State::START_SCREEN)
		{
			window.draw(messageText);
		}

		if (gameState == State::PAUSED)
		{
			window.draw(pauseMessageText);
		}

		// Show everything we just drew
		window.display();
	}
	
	return 0;
}
