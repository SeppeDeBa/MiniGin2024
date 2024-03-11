#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "../3rdParty/imgui-1.90.4/imgui.h"
#include "../3rdParty/imgui-1.90.4/imgui_impl_opengl2.h"
#include "../3rdParty/imgui-1.90.4/imgui_impl_sdl2.h"
#include "../3rdParty/imgui-1.90.4/imgui_plot.h"
#include <chrono>

struct Transform
{
	float matrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};
class GameObject3D
{
public:
	Transform* transform{}; // try again when this is a pointer
	int ID{ 1 };
};
class GameObject3DNoPtr
{
public:
	Transform transform{}; // try again when this is a pointer
	int ID{ 1 };
};

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
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext);
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();//does this not need m_Window?

	ImGui::NewFrame();
	// ======= ADD GUI HERE ========
// to do if I want to use it in project fully: Use functions for readability and decluttering, find a better system for managing the plotConfigs.
	//VARIABLES FOR BOTH EXERCISES
	static int sampleInt = 10;
	static int sampleIntEx3 = 100;
	static bool showGraphEx2 = false;
	static bool showGraphEx3 = false;
	static bool showGraphEx3Alt = false;
	const unsigned int graphsToCombine{ 2 };
	const static ImU32 colors[graphsToCombine] = { ImColor(0, 200, 0), ImColor(0, 120, 80) };


	static ImGui::PlotConfig ex2PlotConfig{};
	static ImGui::PlotConfig ex3PlotConfig{};
	static ImGui::PlotConfig ex3AltPlotConfig{};
	static ImGui::PlotConfig ex3CombinedPlotConfig{};



	//===================================================================================
	//EX 2:

	

	ImGui::Begin("Exercise 2"); // Create a window called "Exercise 2" and append into it.
	ImGui::InputInt("# samples", &sampleInt);
	if (ImGui::Button("Trash the Cache"))
	{
		// == Do Exercise 2 and set draw plot to true==
#pragma region DoEx2
		std::vector <float> elapsedTimeVect;
		int arraySize{ 1'000'000 };
		const int sampleSize{ sampleInt }; //could use original sampleInt, keeping this to stay with the original code of my exercise
		int* dynIntArr = new int[arraySize] {};

		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<long long> iteratorVector{};
			for (int sampleIterator{ 0 }; sampleIterator < sampleSize; ++sampleIterator)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < arraySize; i += stepSize)
				{
					dynIntArr[i] *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				auto timePassed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				//std::cout << "Step " << stepSize << " took " << timePassed / 1000.f << "ms" << std::endl;
				iteratorVector.push_back(timePassed);
			}
			//CALCULATE AVERAGE OF THE ITERATIONS
			long long averageTime{};
			iteratorVector.erase(std::max_element(iteratorVector.begin(), iteratorVector.end()));
			iteratorVector.erase(std::min_element(iteratorVector.begin(), iteratorVector.end()));
			for (long long time : iteratorVector)
			{
				averageTime += time;
			}

			elapsedTimeVect.push_back((float)(averageTime / iteratorVector.size()) / 1000.f);
		}
		const int dataBufferSize{ (int)elapsedTimeVect.size() };

		if (ex2PlotConfig.values.ys != nullptr)
		{
			delete[] ex2PlotConfig.values.ys;
		}
		float* pData = new float[dataBufferSize] {};
		for (size_t i = 0; i < dataBufferSize; ++i)
		{
			pData[i] = elapsedTimeVect[i];
		}

		delete[] dynIntArr;
		//conf.values.xs = x_data; // this line is optional
		//ex2PlotConfig.values.xs = pData;
		ex2PlotConfig.values.ys = pData;
		ex2PlotConfig.values.count = dataBufferSize;
		ex2PlotConfig.scale.min = 0;
		ex2PlotConfig.scale.max = elapsedTimeVect[0];//taking the first since it is often, but not always the largest
		ex2PlotConfig.tooltip.show = true;
		ex2PlotConfig.tooltip.format = "x=%.2f, y=%.3f";
		ex2PlotConfig.grid_x.show = true;
		ex2PlotConfig.grid_y.show = true;
		ex2PlotConfig.frame_size = ImVec2(200, 200);
		ex2PlotConfig.line_thickness = 2.f;
		ex2PlotConfig.values.color = ImColor(200, 100, 0);
		//ex2PlotConfig.values.color = Uint32{  };
		//
		if (!showGraphEx2)
		{
			showGraphEx2 = true;
		}
#pragma endregion DoEx2
	}
	if (showGraphEx2)
	{
		ImGui::Plot("Trash the Cache ex2", ex2PlotConfig);
	}
	ImGui::End();


	//===================================================================================
	//EX 3:
	ImGui::Begin("Exercise 3"); // Create a window called "Exercise 3" and append into it.
	ImGui::InputInt("# samples", &sampleIntEx3);
	if (ImGui::Button("Trash the Cache with GameObject3D"))
	{
#pragma region DoEx3
		//std::cout << std::endl << "Now proceeding to Exercise 2:" << std::endl;

		std::vector <float> elapsedTimeVectEx3;
		int arraySizeEx3{ 1'000'000 };
		const int sampleSizeEx3{ sampleIntEx3 };
		//const int stepSize{ 2 };
		GameObject3DNoPtr* dynGameObjArr = new GameObject3DNoPtr[arraySizeEx3];

		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<long long> iteratorVector{};
			for (int sampleIterator{ 0 }; sampleIterator < sampleSizeEx3; ++sampleIterator)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < arraySizeEx3; i += stepSize)
				{
					dynGameObjArr[i].ID *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				auto timePassed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				//	std::cout << "Step " << stepSize << " took " << timePassed / 1000.f << " ms" << std::endl;
				iteratorVector.push_back(timePassed);
			}

			//CALCULATE AVERAGE OF THE ITERATIONS
			long long averageTime{};
			iteratorVector.erase(std::max_element(iteratorVector.begin(), iteratorVector.end()));
			iteratorVector.erase(std::min_element(iteratorVector.begin(), iteratorVector.end()));
			for (long long time : iteratorVector)
			{
				averageTime += time;
			}

			elapsedTimeVectEx3.push_back((float)(averageTime / iteratorVector.size()) / 1000.f);
		}
		//std::cout << "== FINAL TIMES HERE ==" << std::endl;
		//for (size_t i{}; i < elapsedTimeVectEx3.size(); ++i)
		//{
		//	std::cout << "loop " << i << " was; " << elapsedTimeVectEx3[i] / 1000.f << " ms" << std::endl;
		//}
		const int dataBufferSize{ (int)elapsedTimeVectEx3.size() };
		if (ex3PlotConfig.values.ys != nullptr)
		{
			delete[] ex3PlotConfig.values.ys;
		}
		float* pData = new float[dataBufferSize] {};
		for (size_t i = 0; i < dataBufferSize; ++i)
		{
			pData[i] = elapsedTimeVectEx3[i];
		}

		delete[] dynGameObjArr;
		//conf.values.xs = x_data; // this line is optional
//ex2PlotConfig.values.xs = pData;
		ex3PlotConfig.values.ys = pData;
		ex3PlotConfig.values.count = dataBufferSize;
		ex3PlotConfig.scale.min = 0;
		ex3PlotConfig.scale.max = elapsedTimeVectEx3[0];//taking the first since it is often, but not always the largest
		ex3PlotConfig.tooltip.show = true;
		ex3PlotConfig.tooltip.format = "x=%.2f, y=%.3f";
		ex3PlotConfig.grid_x.show = true;
		ex3PlotConfig.grid_y.show = true;
		ex3PlotConfig.frame_size = ImVec2(200, 80);
		ex3PlotConfig.line_thickness = 2.f;
		ex3PlotConfig.values.color = colors[0];
		if (!showGraphEx3)
		{
			showGraphEx3 = true;
		}
		if (ex3CombinedPlotConfig.scale.max < elapsedTimeVectEx3[0])
		{
			ex3CombinedPlotConfig.scale.max = elapsedTimeVectEx3[0]; //seperate to always have max at the highest possible, not only on the max of the second value clicked
		}



#pragma endregion DoEx3
	}
	if (showGraphEx3)
	{
		ImGui::Plot("Trash the cache ex3Alt", ex3PlotConfig);
	}


	//===================================================================================
		//EX 3 Alt:
	if (ImGui::Button("Trash the Cache with GameObject3DAlt"))
	{
#pragma region DoEx3Alt
		//std::cout << std::endl << "Now proceeding to Exercise 2:" << std::endl;

		std::vector <float> elapsedTimeVectEx3;
		int arraySizeEx3{ 1'000'000 };
		const int sampleSizeEx3{ sampleIntEx3 };
		//const int stepSize{ 2 };
		GameObject3D* dynGameObjArr = new GameObject3D[arraySizeEx3];

		for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<long long> iteratorVector{};
			for (int sampleIterator{ 0 }; sampleIterator < sampleSizeEx3; ++sampleIterator)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < arraySizeEx3; i += stepSize)
				{
					dynGameObjArr[i].ID *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				auto timePassed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				//	std::cout << "Step " << stepSize << " took " << timePassed / 1000.f << " ms" << std::endl;
				iteratorVector.push_back(timePassed);
			}

			//CALCULATE AVERAGE OF THE ITERATIONS
			long long averageTime{};
			iteratorVector.erase(std::max_element(iteratorVector.begin(), iteratorVector.end()));
			iteratorVector.erase(std::min_element(iteratorVector.begin(), iteratorVector.end()));
			for (long long time : iteratorVector)
			{
				averageTime += time;
			}

			elapsedTimeVectEx3.push_back((float)(averageTime / iteratorVector.size()) / 1000.f);
		}
		//std::cout << "== FINAL TIMES HERE ==" << std::endl;
		//for (size_t i{}; i < elapsedTimeVectEx3.size(); ++i)
		//{
		//	std::cout << "loop " << i << " was; " << elapsedTimeVectEx3[i] / 1000.f << " ms" << std::endl;
		//}
		const int dataBufferSize{ (int)elapsedTimeVectEx3.size() };
		if (ex3AltPlotConfig.values.ys != nullptr)
		{
			delete[] ex3AltPlotConfig.values.ys;
		}
		float* pData = new float[dataBufferSize] {};
		for (size_t i = 0; i < dataBufferSize; ++i)
		{
			pData[i] = elapsedTimeVectEx3[i];
		}

		delete[] dynGameObjArr;

		ex3AltPlotConfig.values.ys = pData;
		ex3AltPlotConfig.values.count = dataBufferSize;
		ex3AltPlotConfig.scale.min = 0;
		ex3AltPlotConfig.scale.max = elapsedTimeVectEx3[0];//taking the first since it is often, but not always the largest
		ex3AltPlotConfig.tooltip.show = true;
		ex3AltPlotConfig.tooltip.format = "x=%.2f, y=%.3f";
		ex3AltPlotConfig.grid_x.show = true;
		ex3AltPlotConfig.grid_y.show = true;
		ex3AltPlotConfig.frame_size = ImVec2(200, 80);
		ex3AltPlotConfig.line_thickness = 2.f;
		ex3AltPlotConfig.values.color = colors[1];
		if (!showGraphEx3Alt)
		{
			showGraphEx3Alt = true;
		}
		if (ex3CombinedPlotConfig.scale.max < elapsedTimeVectEx3[0])
		{
			ex3CombinedPlotConfig.scale.max = elapsedTimeVectEx3[0];
		}

#pragma endregion DoEx3Alt
	}
	if (showGraphEx3Alt)
	{
		ImGui::Plot("Trash the cache ex3Alt", ex3AltPlotConfig);
	}

	if (showGraphEx3 && showGraphEx3Alt)
	{
		//TODO: Make this not happen every Reder() call, idea to put certain values that change per click such as values.count in the clicking function itself, maybe some sort of dirty flag could be used?
		const float* y_data[] = { ex3PlotConfig.values.ys, ex3AltPlotConfig.values.ys };
		ex3CombinedPlotConfig.values.ys_list = y_data;
		if (ex3PlotConfig.values.count > ex3AltPlotConfig.values.count)
		{
			ex3CombinedPlotConfig.values.count = ex3PlotConfig.values.count;
		}
		else
		{
			ex3CombinedPlotConfig.values.count = ex3AltPlotConfig.values.count;
		}
		ex3CombinedPlotConfig.values.count = 11; //had to use magic number due to an error in how i calculate the results, or i'm not seeing a better option. Have to work this out of the program!
		ex3CombinedPlotConfig.values.ys_count = graphsToCombine;
		ex3CombinedPlotConfig.scale.min = 0;
		ex3CombinedPlotConfig.tooltip.show = true;
		ex3CombinedPlotConfig.tooltip.format = "x=%.2f, y=%.3f";
		ex3CombinedPlotConfig.grid_x.show = true;
		ex3CombinedPlotConfig.grid_y.show = true;
		ex3CombinedPlotConfig.frame_size = ImVec2(200, 80);
		ex3CombinedPlotConfig.line_thickness = 2.f;
		ex3CombinedPlotConfig.grid_x.size = 10.f;
		ex3CombinedPlotConfig.values.colors = colors;
		ImGui::Text("Combined: ");
		ImGui::Plot("Combined", ex3CombinedPlotConfig);
	}


	ImGui::End();



	//ImGui::ShowDemoWindow();
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

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
