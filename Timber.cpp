#include <SFML/Graphics.hpp>

using namespace sf;

const float TREE_H_POS = 810;
const float TREE_V_POS = 0;
const float BEE_H_POS = 0;
const float BEE_V_POS = 800;

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
	
	while (window.isOpen()) {
		// Handle Player input
		
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		
		// Update scene
		
		
		// Draw scene
		
		// Clear everything from last frame
		window.clear();
		
		// Draw game scene
		window.draw(spriteBackground);
		window.draw(spriteTree);
		window.draw(spriteBee);
		
		// Show everything we just drew
		window.display();
	}
	
	return 0;
}
