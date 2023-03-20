#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "..\3rdParty\imgui\imgui_impl_sdl2.h"
#include "..\3rdParty\imgui\imgui_plot.h"
#include "..\3rdParty\imgui\imgui_impl_opengl2.h"
#include "..\3rdParty\imgui\imgui.h"
#include <chrono>
constexpr size_t buf_size = 10;

static float y_data[buf_size];
static float y_data2[buf_size];
static float y_data3[buf_size];
int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();


	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	ImGui::Begin("Exercise 1");
	static int i0 = 10;
	ImGui::InputInt("# samples", &i0);
	static int firstButtonClick = 0;
	static int secondButtonClick = 0;
	static int thirdButtonClick = 0;
	static int fourthButton = 0;



	if (ImGui::Button("Trash the cache"))
	{
		ImGui::Text("Please wait...");
		GenerateDataExercise01(i0);
		firstButtonClick++;
	}
	if (firstButtonClick & 1)
	{
		ImGui::PlotConfig conf; 
		conf.values.ys = y_data;
		conf.values.count = buf_size;
		conf.values.color = ImColor(0, 255, 0);
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("plot", conf);
		//ImGui::PlotLines("plot1", y_data, buf_size, 0, (const char*)0, 10.f, 50.f, ImVec2(200.f, 100.f));
	}

	ImGui::End();

	ImGui::Begin("Exercise 2");
	static int i1 = 100;
	//	GenerateData(i1);
	ImGui::InputInt("# samples", &i1);
	if (ImGui::Button("Trash the cache with GameObject"))
	{
		ImGui::Text("Please wait...");
		secondButtonClick++;
		GenerateDataExercise02(i1);
	}
	if (secondButtonClick & 1)
	{
		ImGui::PlotConfig conf;
		conf.values.ys = y_data2;
		conf.values.count = buf_size;
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.values.color = ImColor(255, 0, 0);
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("plot", conf);
		//ImGui::PlotLines("plot2", y_data2, buf_size, 0, (const char*)0, 10.f, 50.f, ImVec2(200.f, 100.f));

	}

	//start plot

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		//start plot
		ImGui::Text("Please wait...");
		GenerateDataExercise02Alt(i1);
		thirdButtonClick++;
	}
	if (thirdButtonClick & 1)
	{
		ImGui::PlotConfig conf; 
		conf.values.ys = y_data3;
		conf.values.count = buf_size;
		conf.values.color = ImColor(0, 255, 0);
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("plot", conf);
	
		//ImGui::PlotLines("plot3", y_data3, buf_size,0,(const char*)0,10.f,50.f,ImVec2(200.f,100.f));

	}
	if (ImGui::Button("Trash the cache with Combined"))
	{
		//start plot
		ImGui::Text("Please wait...");
		fourthButton++;
	}
	if (fourthButton & 1)
	{
		const float* y_datas[] = { y_data2, y_data3 };
		ImU32 colors[2] = { ImColor(255, 0, 0) ,ImColor(0, 255, 0) };
		ImGui::PlotConfig conf; // this line is optional
		conf.values.ys_list = y_datas;
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.values.count = buf_size;
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.grid_x.show = true;
		conf.grid_y.size = 2.f;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("plot", conf);

	}
	ImGui::End();

	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();


	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }


void dae::Renderer::GenerateDataExercise01(const int& data) const
{
	std::vector<float> durationArr;
	std::vector<int> gameobjectArr;
	gameobjectArr.resize(data);

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		const auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < data; i += stepsize)
		{
			gameobjectArr[i] *= 2;
		}
		const auto end = std::chrono::high_resolution_clock::now();
		const auto duration = duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000.f;
		durationArr.emplace_back(duration);

	}
	for (int i = 0; i < 10; i++)
	{
		y_data[i] = durationArr[i];
	}
}
void dae::Renderer::GenerateDataExercise02(const int& data) const
{

	std::vector<float> durationArr;
	std::vector<GameObject3D> gameobjectArr;
	gameobjectArr.resize(data);
	
	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{

		const auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < data; i += stepsize)
		{
			gameobjectArr[i].ID *= 2;
		}
		const auto end = std::chrono::high_resolution_clock::now();
		const auto duration = duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000.f;
		durationArr.emplace_back(duration);
	}
	for (int i = 0; i < 10; i++)
	{
		y_data2[i] = durationArr[i];
	}
}
void dae::Renderer::GenerateDataExercise02Alt(const int& data) const
{
	//alternative -> use pointers
	std::vector<GameObject3DAlternative> gameobjectArrAlt{};

	gameobjectArrAlt.resize(data);
	std::vector<float> durationArr;
	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{

		const auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < data; i += stepsize)
		{
			gameobjectArrAlt[i].ID *= 2;
		}
		const auto end = std::chrono::high_resolution_clock::now();
		const auto duration = duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000.f;
		durationArr.emplace_back(duration);
	}
	for (int i = 0; i < 10; i++)
	{
		y_data3[i] = durationArr[i];
	}
}
