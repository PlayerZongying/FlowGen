#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "FlowGUI.h"
#include <glm/glm.hpp>
#include <src/FlowGL/VirtualObject.h>
#include <string>
#include "ObjectEntry.h"

#include "ShaderEditor.h"
#include "ResourceEditor.h"

#define itoc(a) ((char*)(intptr_t)(a))

Flow::FlowGUI::FlowGUI(GLFWwindow* aWindow, ResourceHandler* aResourceHandler)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(aWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	myResources = aResourceHandler;

	myCurrentEditor = ECurrentEditor::COUNT;

	myShaderEditor = new ShaderEditor();
	myResourceEditor = new ResourceEditor(myResources);
}



Flow::FlowGUI::~FlowGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

int selectedItem = -1;
bool alwaysTrue = true;

void Flow::FlowGUI::Render(std::vector<VirtualObject*> someObjects)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	ImGui::Begin("Flow", &alwaysTrue, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Shader Editor", "Ctrl+O"))		{ myCurrentEditor = ECurrentEditor::EShaderEditor;		}
			if (ImGui::MenuItem("Resource Viewer", "Ctrl+S"))	{ myCurrentEditor = ECurrentEditor::EResourceViewer;	}
			if (ImGui::MenuItem("Object Hierarchy", "Ctrl+W"))	{ myCurrentEditor = ECurrentEditor::EObjectHierarchy;	}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	switch (myCurrentEditor)
	{
	case Flow::ECurrentEditor::EObjectHierarchy:

		UpdateHierarchy(someObjects);

		break;

	case Flow::ECurrentEditor::EShaderEditor:

		myShaderEditor->Update();

		break;

	case Flow::ECurrentEditor::EResourceViewer:

		myResourceEditor->Update();

		break;

	case Flow::ECurrentEditor::COUNT:
		break;

	default:
		break;
	}

	

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Flow::FlowGUI::UpdateHierarchy(std::vector<VirtualObject*> someObjects)
{
	if(ImGui::Button("Create Object"))
	{
	
	}

	if (someObjects.size() != myObjectEntries.size())
	{
		RepopulateEntries(someObjects);
	}

	ImGui::BeginChild("Scrolling");
	for (size_t i = 0; i < myObjectEntries.size(); i++)
	{
		std::string number = std::to_string(i);
		std::string Title = "Object " + number;

		if (ImGui::Button(Title.c_str()))
		{
			myObjectEntries[i]->Opened = !myObjectEntries[i]->Opened;
			selectedItem = i;
		}

		if (!myObjectEntries[i]->Opened)
		{
			continue;
		}

		if (selectedItem == i)
		{
			myObjectEntries[i]->Update();
		}
		else
		{
			myObjectEntries[i]->Opened = false;
		}
	}
	ImGui::EndChild();
}

void Flow::FlowGUI::RepopulateEntries(std::vector<VirtualObject*> someObjects)
{
	for (size_t i = 0; i < myObjectEntries.size(); i++)
	{
		delete myObjectEntries[i];
	}

	myObjectEntries.clear();

	for (size_t i = 0; i < someObjects.size(); i++)
	{
		ObjectEntry* e = new ObjectEntry(someObjects[i]);

		myObjectEntries.push_back(e);
	}
}
