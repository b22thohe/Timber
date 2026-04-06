#include <SFML/Graphics.hpp>

using namespace sf;

// This is where the game starts from int main()
int main() {
	// Create a video mode object
	VideoMode vm(1920, 1080);
	
	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!", Style::Fullscreen);
	
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
