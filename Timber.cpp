#include <SFML/Graphics.hpp>

using namespace sf;

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
		
		// Show everything we just drew
		window.display();
	}
	
	return 0;
}
