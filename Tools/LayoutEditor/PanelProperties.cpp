/*!
	@file
	@author		Georgiy Evmenov
	@date		09/2008
*/

#include "Precompiled.h"
#include "Localise.h"
#include "PanelProperties.h"
#include "EditorWidgets.h"
#include "SettingsManager.h"

namespace tools
{
	PanelProperties::PanelProperties() :
		BasePanelViewItem("PanelProperties.layout"),
		mPropertyItemHeight(0)
	{
	}

	void PanelProperties::initialise()
	{
		mPanelCell->setCaption(replaceTags("Widget_type_propertes"));
		mPropertyItemHeight = SettingsManager::getInstance().getSector("Settings")->getPropertyValue<int>("PropertyItemHeight");
	}

	void PanelProperties::shutdown()
	{
		destroyPropertyFields();
	}

	size_t PanelProperties::AddParametrs(WidgetStyle* widgetType, WidgetContainer* widgetContainer, int& y, MyGUI::Widget* _currentWidget)
	{
		size_t count = widgetType->parameter.size();

		for (MyGUI::VectorStringPairs::iterator iter = widgetType->parameter.begin(); iter != widgetType->parameter.end(); ++iter)
		{
			std::string value = "";
			for (MyGUI::VectorStringPairs::iterator iterProperty = widgetContainer->mProperty.begin(); iterProperty != widgetContainer->mProperty.end(); ++iterProperty)
			{
				if (iterProperty->first == iter->first)
				{
					value = iterProperty->second;
					break;
				}
			}

			PropertyField field;
			field.createPropertiesWidgetsPair(mWidgetClient, iter->first, value, iter->second, y, _currentWidget, nullptr);
			mFields.push_back(field);

			y += mPropertyItemHeight;
		}

		return count;
	}

	void PanelProperties::update(MyGUI::Widget* _currentWidget, WidgetStyle* _widgetType)
	{
		destroyPropertyFields();

		if (_widgetType == nullptr)
		{
			setVisible(false);
			return;
		}

		int y = 0;

		WidgetContainer* widgetContainer = EditorWidgets::getInstance().find(_currentWidget);

		MyGUI::LanguageManager::getInstance().addUserTag("widget_type", _widgetType->name);

		mPanelCell->setCaption(MyGUI::LanguageManager::getInstance().replaceTags("#{Widget_type_propertes}"));

		size_t count = AddParametrs(_widgetType, widgetContainer, y, _currentWidget);

		setVisible(count > 0);

		mPanelCell->setClientHeight(y);
	}

	void PanelProperties::destroyPropertyFields()
	{
		for (VectorPropertyField::iterator item = mFields.begin(); item != mFields.end(); ++ item)
			(*item).destroy();
		mFields.clear();
	}

} // namespace tools
