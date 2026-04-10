#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

/* PROTOTYPES */
void centerText(Text& text, Vector2f position);

void updateCloud(Sprite& cloud, float& speed, bool& active, float dt, int screenWidth);

void updateBranches(int seed);

const float TREE_H_POS = 810;
const float TREE_V_POS = 0;
const float BEE_H_POS = 0;
const float BEE_V_POS = 800;
const float CLOUD1_V_POS = 0;
const float CLOUD2_V_POS = 250;
const float CLOUD3_V_POS = 500;
const int NUM_BRANCHES = 6;

enum class State { PAUSED, PLAYING, GAME_OVER, START_SCREEN };
enum class Side { LEFT, RIGHT, NONE };

Sprite branches[NUM_BRANCHES];
Side branchPositions[NUM_BRANCHES];

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

	// Prepare branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	// Set texture on branches
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set sprite's origin to center
		branches[i].setOrigin(220, 20);
	}

	// Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	// Player starts on the left
	Side playerSide = Side::LEFT;

	// Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	// Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line up the axe with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Log related varibales
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Player input control
	bool acceptInput = false;

	while (window.isOpen()) {

		/* 1. Handle Events */
		Event event;
		while (window.pollEvent(event)) {
		    if (event.type == Event::Closed)
		        window.close();

		    // Reset acceptInput when the user lets go of a key
		    if (event.type == Event::KeyReleased && gameState == State::PLAYING) {
		        acceptInput = true;
		        // Hide the axe when they let go
		        spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
		    }

		    if (event.type == Event::KeyPressed) {
		        // Handle ESCAPE
		        if (event.key.code == Keyboard::Escape) window.close();

		        // Handle SPACE
		        if (event.key.code == Keyboard::Space) {
		            if (gameState == State::START_SCREEN) gameState = State::PLAYING;
		            else if (gameState == State::PLAYING) gameState = State::PAUSED;
		            else if (gameState == State::PAUSED)  gameState = State::PLAYING;
		            // Note: Game Over is handled by Enter or Space depending on preference
		            else if (gameState == State::GAME_OVER) {
		                // Quick reset for Space
		                score = 0;
		                timerRemaining = 6.0f;
		                gameState = State::PLAYING;
		            }
		        }

		        // Handle ENTER (Hard Reset)
		        if (event.key.code == Keyboard::Enter) {
		            gameState = State::START_SCREEN;
		            messageText.setString("Press <SPACE> to start!");
		            centerText(messageText, Vector2f(1920 / 2.0f, 1080 / 2.0f));
		            score = 0;
		            timerRemaining = 6.0f;
		            beeActive = false;
		            cloud1Active = false;
		            cloud2Active = false;
		            cloud3Active = false;
		            for (int i = 0; i < NUM_BRANCHES; i++) branchPositions[i] = Side::NONE;
		            spriteRIP.setPosition(675, 2000);
		            spritePlayer.setPosition(580, 720);
		            acceptInput = true;
		        }

		        /* Handle THE CHOP (Only if playing and input is accepted) */
		        if (gameState == State::PLAYING && acceptInput) {

		            if (event.key.code == Keyboard::Right) {
		                playerSide = Side::RIGHT;
		                score++;
		                timerRemaining += (2.0f / score) + 0.15f;
		                spriteAxe.setPosition(AXE_POSITION_RIGHT, 830);
		                spritePlayer.setPosition(1200, 720);
		                updateBranches(score);
		                spriteLog.setPosition(810, 720);
		                logSpeedX = -5000;
		                logActive = true;
		                acceptInput = false; // Stop further chops until key is released
		            }

		            if (event.key.code == Keyboard::Left) {
		                playerSide = Side::LEFT;
		                score++;
		                timerRemaining += (2.0f / score) + 0.15f;
		                spriteAxe.setPosition(AXE_POSITION_LEFT, 830);
		                spritePlayer.setPosition(580, 720);
		                updateBranches(score);
		                spriteLog.setPosition(810, 720);
		                logSpeedX = 5000;
		                logActive = true;
		                acceptInput = false; // Stop further chops until key is released
		            }
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
				messageText.setString("Time is up!");
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

			// Update branches
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;

				if (branchPositions[i] == Side::LEFT)
				{
					// Move sprite to left
					branches[i].setPosition(610, height);
					// Flip the sprite
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == Side::RIGHT)
				{
					// Move sprite right
					branches[i].setPosition(1330, height);
					// Set sprite rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					// If neither left or right --> Hide the branch
					branches[i].setPosition(3000, height);
				}

			}
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
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		window.draw(spriteTree);

		// Draw the player
		window.draw(spritePlayer);

		// Draw the axe
		window.draw(spriteAxe);

		// Draw the flying log
		window.draw(spriteLog);

		// Draw the tombstone
		window.draw(spriteRIP);

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

/* Helper functions */

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

// Function for moving branches
void updateBranches(int seed)
{
	// Move all branches down one place
	for (int j = NUM_BRANCHES-1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at pos 0
	// LEFT, RIGHT, or NONE
	srand((int)time(0)+seed);
	int r = (rand() % 5);

	switch (r)
	{
	case 0:
		branchPositions[0] = Side::LEFT;
		break;
	case 1:
		branchPositions[0] = Side::RIGHT;
		break;
	default:
		branchPositions[0] = Side::NONE;
		break;
	}
}
