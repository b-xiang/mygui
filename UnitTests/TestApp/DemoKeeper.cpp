#include "Precompiled.h"
#include "DemoKeeper.h"
#include "Base/Main.h"
#include "WrapPanel.h"
#include "StackPanel.h"
#include "ScrollViewPanel.h"
#include "HyperTextBox.h"

namespace demo
{

	DemoKeeper::DemoKeeper()
	{
	}

	void DemoKeeper::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(getRootMedia() + "/UnitTests/TestApp");
		addResourceLocation(getRootMedia() + "/Common/Tools");
	}

	void DemoKeeper::createScene()
	{
		MyGUI::ResourceManager::getInstance().load("FrameworkFonts.xml");
		MyGUI::ResourceManager::getInstance().load("Fonts.xml");
		MyGUI::ResourceManager::getInstance().load("HyperTextSkins.xml");

		MyGUI::FactoryManager::getInstance().registerFactory<MyGUI::WrapPanel>("Widget");
		MyGUI::FactoryManager::getInstance().registerFactory<MyGUI::StackPanel>("Widget");
		MyGUI::FactoryManager::getInstance().registerFactory<MyGUI::ScrollViewPanel>("Widget");
		MyGUI::FactoryManager::getInstance().registerFactory<MyGUI::HyperTextBox>("Widget");

		MyGUI::Window* window = MyGUI::Gui::getInstance().createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(10, 10, 500, 500), MyGUI::Align::Default, "Main");
		MyGUI::IntCoord coord = window->getClientCoord();

		MyGUI::HyperTextBox* hyperText = window->createWidget<MyGUI::HyperTextBox>("HyperTextBox", MyGUI::IntCoord(0, 0, coord.width, coord.height), MyGUI::Align::Stretch);
		hyperText->eventUrlClick += MyGUI::newDelegate(this, &DemoKeeper::OnClickUrl);

		hyperText->addItem("<p align='left'><h1>Caption1 left</h1></p>");
		hyperText->addItem("<p align='center'><h2>Caption2 center</h2></p>");
		hyperText->addItem("<p align='right'><h3>Caption3 right</h3></p>");
		hyperText->addItem("<p><s>This is strike.</s></p>");
		hyperText->addItem("<p><s><color value='#FF00FF'>This is strike and colour.</color></s></p>");
		hyperText->addItem("<p><u>This is under.</u></p>");
		hyperText->addItem("<p><color value='#FFFFFF'>This is color.</color></p>");
		hyperText->addItem("<p><url value='http://www.google.com'>http://www.google.com</url></p>");
		hyperText->addItem("<p>This is image.<img>HandPointerImage</img></p>");
		hyperText->addItem("<p><b>This is bold text.</b></p>");
		hyperText->addItem("<p><i>This is italic text.</i></p>");
		hyperText->addItem("<p><i><b>This is bold and italic text.</b></i></p>");
		hyperText->addItem("<p><i><b><s><u>This is bold and italic and under and strike text.</u></s></b></i></p>");
		//hyperText->addItem("<p>This is user tag.<character>user</character></p>");
		hyperText->addItem("<p float='left'><img width='48' height='48'>HandPointerImage</img>text1 texttext2 text3 text4 texttext5 texttexttexttext6 text7 text8 texttext9 text10 texttext11 text12</p>");
		hyperText->addItem("<p float='right' align='right'><img width='48' height='48'>HandPointerImage</img>text1 texttext2 text3 text4 texttext5 texttexttexttext6 text7 text8 texttext9 text10 texttext11 text12</p>");

		hyperText->updateContent();
	}

	void DemoKeeper::destroyScene()
	{
		MyGUI::FactoryManager::getInstance().unregisterFactory<MyGUI::HyperTextBox>("Widget");
		MyGUI::FactoryManager::getInstance().unregisterFactory<MyGUI::ScrollViewPanel>("Widget");
		MyGUI::FactoryManager::getInstance().unregisterFactory<MyGUI::StackPanel>("Widget");
		MyGUI::FactoryManager::getInstance().unregisterFactory<MyGUI::WrapPanel>("Widget");
	}

	void DemoKeeper::OnClickUrl(MyGUI::HyperTextBox* _sender, const std::string& _url)
	{
		int test = 0;
	}

} // namespace demo

MYGUI_APP(demo::DemoKeeper)
