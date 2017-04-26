// MAIN.CPP

#include "constants.h"
#include "graphics.h"
#include "UI.h"
#include "Control.h"

Control C;

// functions
void process_input();
void update();
void render();
void generate();
void show_title_screen();
bool is_colliding(SDL_Rect &a, SDL_Rect &b);
double current_time();
void createNumberFont(vector<Control>& newvector, SDL_Texture* texture, TTF_Font* font);
SDL_Texture* createFont(TTF_Font * font, const char * whatTheFontIs, SDL_Texture * whereToStore);
void createNumberFont(vector<Control>& newvector, SDL_Texture* texture, TTF_Font* font, int numbers);

// global objects
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
Panel panel;

vector<Balloon> balloons;
vector<Control> ControlVec;
vector<Control> ScoreVec;

// global variables
bool running = true, fullscreen = false;
double delta_time, old_time;
const double FPS = 60.0;
int timer = 60;
float faster = 0.0001f;

int randomPanelNum = rand() % 29;
int panelNum = 0;
// key map
std::array<bool, 2> buttons;

int main(int argc, char* argv[])
{
	srand(NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
	}
	else cout << "Initialised SDL\n";

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_image init error: %s\n", IMG_GetError());
	}
	else cout << "Initialised SDL_image\n";

	if (TTF_Init() == -1) {
		cout << "SDL_ttf init error\n";
	}
	else cout << "Initialised SDL_ttf\n";

	// Building key map
	buttons[0]		= false;   // esc
	buttons[1]		= false;   // fullscreen

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
	cout << "Window created\n";

	SDL_SetWindowTitle(window, "Balloons");
	SDL_SetRenderDrawColor(renderer, 255, 255, 180, 255);

	cout << "Entering title screen\n";
	show_title_screen();

	TTF_Font *font = TTF_OpenFont("../assets/arial.ttf", 100);
	TTF_Font *scoreFont = TTF_OpenFont("../assets/arial.ttf", 30);

	createNumberFont(ControlVec, C.font, font);
	createNumberFont(ScoreVec, C.numbersTexture, scoreFont, 10);

	C.scoreTexture = createFont(scoreFont, "Score: ", C.scoreTexture);
	SDL_QueryTexture(C.scoreTexture, NULL, NULL, &C.scoreRect.w, &C.scoreRect.h);

	//SDL_SetWindowPosition(window, 0, 0);

	while (running)
	{
		generate();
		cout << "Level generated\n";

		cout << "\nStart game loop\n";
		while (running) {
			delta_time = current_time() - old_time;

			if (delta_time > 1000.0 / FPS) {

				process_input();
				update();
				render();

				old_time = current_time();
			}
			else
			{
				//faster += 0.001f; // makes it faster
				//cout << faster << endl;
				SDL_Delay(1);
			}
		}

		cout << "End game loop\n\n";
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	cout << "Destroyed SDL objects\n";
	renderer = NULL;
	window = NULL;
	cout << "Cleared object pointers\n";
	TTF_Quit();
	cout << "Quit SDL_ttf\n";
	IMG_Quit();
	cout << "Quit SDL_image\n";
	SDL_Quit();
	cout << "Quit SDL\n";

	return 0;
}

void process_input()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			buttons[0] = true;
			break;
		case SDLK_f:
			C.score1++;
			break;
		case SDLK_r:
			randomPanelNum = rand() % 29;
			/// THIS IS THE NUMBER TO PUT IN THE ARRAY NOT THE ACTUAL NUMBER 
			panelNum = randomPanelNum;//sets the panel num as the random panel num so we can check the values  - if they match.
			/// ------------------------------------------------------------------------
			cout << panelNum << endl;
			break;
		}
		break;
	case SDL_QUIT:
		buttons[0] = true;
		break;
	case SDL_FINGERDOWN:
		int touchPosition_x = event.tfinger.x * SCREEN_WIDTH;
		int touchPosition_y = event.tfinger.y * SCREEN_HEIGHT;
		for (int i = 0; i < balloons.size(); i++)
		{
			if (touchPosition_x > balloons[i].position.x && touchPosition_x < balloons[i].position.x + balloons[i].dimensions.x
				&& touchPosition_y > balloons[i].position.y && touchPosition_y < balloons[i].position.y + balloons[i].dimensions.y)
			{
				vector<Balloon>::iterator iter = balloons.begin() + i;
				balloons.erase(iter);
			}
		}
	break;

	}
}

void update()
{
	if (buttons[0])
	{
		cout << "Exiting...\n";
		running = false;
		buttons[0] = false;
	}

	if (timer == 0)
	{
		balloons.emplace_back(Balloon(renderer, "../assets/ball.png", rand() % (SCREEN_WIDTH - BALLOON_WIDTH), SCREEN_HEIGHT, BALLOON_WIDTH, BALLOON_HEIGHT));
		balloons.back().velocity.y = (-1.3 - faster);

		timer = 120;
	}
	else timer -= 1;

		for (int i = 0; i < balloons.size(); i++)
		{
			balloons[i].update();
			
			if (balloons[i].dst.y < (0 + BALLOON_HEIGHT))
			{
				if (balloons[i].ballonValue == panelNum)
				{
					//game over
					running = false;
				}
				else
				{
					//nothing
				}
			}
		}
}

void render()
{
	SDL_RenderClear(renderer);

	for (int i = 0; i < balloons.size(); i++) balloons[i].render(ControlVec);

	panel.render(ControlVec, randomPanelNum);

	SDL_RenderCopy(renderer, C.scoreTexture, NULL, &C.scoreRect);

	if (C.score1 > 9)
	{
		if (C.score0 > 9)
		{
			C.score0 = 0;
		}
		C.score1 = 0;
		C.score0++;
	}

	SDL_RenderCopy(renderer, ScoreVec[C.score0].font, NULL, &C.numberRect0);
	SDL_RenderCopy(renderer, ScoreVec[C.score1].font, NULL, &C.numberRect1);

	SDL_RenderPresent(renderer);
}

void generate()
{
	panel = Panel(renderer, "../assets/square.png", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 100, 100);
}

void show_title_screen()
{
	bool in_menus = true;

	while (running && in_menus) {
		delta_time = current_time() - old_time;

		if (delta_time > 1000.0 / FPS) {

			SDL_PollEvent(&event);

			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_RETURN:
					cout << "Leaving title screen\n";
					in_menus = false;
					break;
				case SDLK_ESCAPE:
					cout << "Exiting...\n";
					running = false;
					break;
				}
				break;

			case SDL_FINGERDOWN:
				cout << "Leaving title screen\n";
				in_menus = false;
				break;

			case SDL_QUIT:
				cout << "Exiting...\n";
				running = false;
				break;
			}

			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);

			old_time = current_time();
		}
		else
		{
			SDL_Delay(1);
		}
	}
}

bool is_colliding(SDL_Rect &a, SDL_Rect &b) {
	bool collision = true;

	if (a.y + a.h <= b.y) {
		collision = false;
	}
	else if (a.y >= b.y + b.h)
	{
		collision = false;
	}
	else if (a.x + a.w <= b.x)
	{
		collision = false;
	}
	else if (a.x >= b.x + b.w)
	{
		collision = false;
	}

	return collision;
}

double current_time()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void createNumberFont(vector<Control>& newvector, SDL_Texture* texture, TTF_Font* font)
{
	for (int i = 0; i < 30; i++)
	{
		cout << C.numbers[i] << endl;
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, C.numbers[i], C.black);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textSurface = nullptr;
		SDL_FreeSurface(textSurface);
		newvector.emplace_back(texture);
	}
}

void createNumberFont(vector<Control>& newvector, SDL_Texture* texture, TTF_Font* font, int numbers)
{
	for (int i = 0; i < numbers; i++)
	{
		cout << C.score[i] << endl;
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, C.score[i], C.black);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textSurface = nullptr;
		SDL_FreeSurface(textSurface);
		newvector.emplace_back(texture);
	}
}

SDL_Texture* createFont(TTF_Font * font, const char * whatTheFontIs, SDL_Texture * whereToStore)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, whatTheFontIs, C.black);
	SDL_Texture* newt = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = nullptr;
	SDL_FreeSurface(textSurface);
	return newt;
}