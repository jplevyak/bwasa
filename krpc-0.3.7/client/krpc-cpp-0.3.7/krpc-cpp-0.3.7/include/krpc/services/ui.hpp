#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <krpc/service.hpp>
#include <krpc/encoder.hpp>
#include <krpc/decoder.hpp>
#include <krpc/stream.hpp>

namespace krpc {
namespace services {

class UI : public Service {
 public:
  explicit UI(Client* client);

  // Class forward declarations
  class Button;
  class Canvas;
  class InputField;
  class Panel;
  class RectTransform;
  class Text;

  /**
   * Font style.
   */
  enum struct FontStyle {
    /**
     * Normal.
     */
    normal = 0,
    /**
     * Bold.
     */
    bold = 1,
    /**
     * Italic.
     */
    italic = 2,
    /**
     * Bold and italic.
     */
    bold_and_italic = 3
  };

  /**
   * Message position.
   */
  enum struct MessagePosition {
    /**
     * Bottom center.
     */
    bottom_center = 0,
    /**
     * Top center.
     */
    top_center = 1,
    /**
     * Top left.
     */
    top_left = 2,
    /**
     * Top right.
     */
    top_right = 3
  };

  /**
   * Text alignment.
   */
  enum struct TextAlignment {
    /**
     * Left aligned.
     */
    left = 0,
    /**
     * Right aligned.
     */
    right = 1,
    /**
     * Center aligned.
     */
    center = 2
  };

  /**
   * Text alignment.
   */
  enum struct TextAnchor {
    /**
     * Lower center.
     */
    lower_center = 0,
    /**
     * Lower left.
     */
    lower_left = 1,
    /**
     * Lower right.
     */
    lower_right = 2,
    /**
     * Middle center.
     */
    middle_center = 3,
    /**
     * Middle left.
     */
    middle_left = 4,
    /**
     * Middle right.
     */
    middle_right = 5,
    /**
     * Upper center.
     */
    upper_center = 6,
    /**
     * Upper left.
     */
    upper_left = 7,
    /**
     * Upper right.
     */
    upper_right = 8
  };

  /**
   * Add a new canvas.
   *
   * If you want to add UI elements to KSPs stock UI canvas, use UI::stock_canvas.
   */
  UI::Canvas add_canvas();

  /**
   * Remove all user interface elements.
   * @param clientOnly If true, only remove objects created by the calling client.
   */
  void clear(bool client_only);

  /**
   * Display a message on the screen.
   *
   * The message appears just like a stock message, for example quicksave or quickload messages.
   * @param content Message content.
   * @param duration Duration before the message disappears, in seconds.
   * @param position Position to display the message.
   */
  void message(std::string content, float duration, UI::MessagePosition position);

  /**
   * The stock UI canvas.
   */
  UI::Canvas stock_canvas();

  ::krpc::Stream<UI::Canvas> add_canvas_stream();

  ::krpc::Stream<UI::Canvas> stock_canvas_stream();

  /**
   * A text label. See UI::Panel::add_button.
   */
  class Button : public krpc::Object<Button> {
   public:
    explicit Button(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the UI object.
     */
    void remove();

    /**
     * Whether the button has been clicked.
     *
     * This property is set to true when the user clicks the button.
     * A client script should reset the property to false in order to detect subsequent button presses.
     */
    bool clicked();

    /**
     * Whether the UI object is visible.
     */
    void set_visible(bool value);

    /**
     * Whether the button has been clicked.
     *
     * This property is set to true when the user clicks the button.
     * A client script should reset the property to false in order to detect subsequent button presses.
     */
    void set_clicked(bool value);

    /**
     * Whether the UI object is visible.
     */
    bool visible();

    /**
     * The rect transform for the text.
     */
    UI::RectTransform rect_transform();

    /**
     * The text for the button.
     */
    UI::Text text();

    ::krpc::Stream<bool> clicked_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::Stream<UI::RectTransform> rect_transform_stream();

    ::krpc::Stream<UI::Text> text_stream();
  };

  /**
   * A canvas for user interface elements. See UI::stock_canvas and UI::add_canvas.
   */
  class Canvas : public krpc::Object<Canvas> {
   public:
    explicit Canvas(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Add a button to the canvas.
     * @param content The label for the button.
     * @param visible Whether the button is visible.
     */
    UI::Button add_button(std::string content, bool visible);

    /**
     * Add an input field to the canvas.
     * @param visible Whether the input field is visible.
     */
    UI::InputField add_input_field(bool visible);

    /**
     * Create a new container for user interface elements.
     * @param visible Whether the panel is visible.
     */
    UI::Panel add_panel(bool visible);

    /**
     * Add text to the canvas.
     * @param content The text.
     * @param visible Whether the text is visible.
     */
    UI::Text add_text(std::string content, bool visible);

    /**
     * Remove the UI object.
     */
    void remove();

    /**
     * Whether the UI object is visible.
     */
    void set_visible(bool value);

    /**
     * The rect transform for the canvas.
     */
    UI::RectTransform rect_transform();

    /**
     * Whether the UI object is visible.
     */
    bool visible();

    ::krpc::Stream<UI::Button> add_button_stream(std::string content, bool visible);

    ::krpc::Stream<UI::InputField> add_input_field_stream(bool visible);

    ::krpc::Stream<UI::Panel> add_panel_stream(bool visible);

    ::krpc::Stream<UI::Text> add_text_stream(std::string content, bool visible);

    ::krpc::Stream<UI::RectTransform> rect_transform_stream();

    ::krpc::Stream<bool> visible_stream();
  };

  /**
   * An input field. See UI::Panel::add_input_field.
   */
  class InputField : public krpc::Object<InputField> {
   public:
    explicit InputField(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the UI object.
     */
    void remove();

    /**
     * Whether the UI object is visible.
     */
    void set_visible(bool value);

    /**
     * The rect transform for the input field.
     */
    UI::RectTransform rect_transform();

    /**
     * Whether the input field has been changed.
     *
     * This property is set to true when the user modifies the value of the input field.
     * A client script should reset the property to false in order to detect subsequent changes.
     */
    void set_changed(bool value);

    /**
     * Whether the input field has been changed.
     *
     * This property is set to true when the user modifies the value of the input field.
     * A client script should reset the property to false in order to detect subsequent changes.
     */
    bool changed();

    /**
     * The value of the input field.
     */
    std::string value();

    /**
     * Whether the UI object is visible.
     */
    bool visible();

    /**
     * The text component of the input field.
     *
     * Use UI::InputField::value to get and set the value in the field.
     * This object can be used to alter the style of the input field's text.
     */
    UI::Text text();

    /**
     * The value of the input field.
     */
    void set_value(std::string value);

    ::krpc::Stream<UI::RectTransform> rect_transform_stream();

    ::krpc::Stream<bool> changed_stream();

    ::krpc::Stream<std::string> value_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::Stream<UI::Text> text_stream();
  };

  /**
   * A container for user interface elements. See UI::Canvas::add_panel.
   */
  class Panel : public krpc::Object<Panel> {
   public:
    explicit Panel(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Add a button to the panel.
     * @param content The label for the button.
     * @param visible Whether the button is visible.
     */
    UI::Button add_button(std::string content, bool visible);

    /**
     * Add an input field to the panel.
     * @param visible Whether the input field is visible.
     */
    UI::InputField add_input_field(bool visible);

    /**
     * Create a panel within this panel.
     * @param visible Whether the new panel is visible.
     */
    UI::Panel add_panel(bool visible);

    /**
     * Add text to the panel.
     * @param content The text.
     * @param visible Whether the text is visible.
     */
    UI::Text add_text(std::string content, bool visible);

    /**
     * Remove the UI object.
     */
    void remove();

    /**
     * Whether the UI object is visible.
     */
    void set_visible(bool value);

    /**
     * The rect transform for the panel.
     */
    UI::RectTransform rect_transform();

    /**
     * Whether the UI object is visible.
     */
    bool visible();

    ::krpc::Stream<UI::Button> add_button_stream(std::string content, bool visible);

    ::krpc::Stream<UI::InputField> add_input_field_stream(bool visible);

    ::krpc::Stream<UI::Panel> add_panel_stream(bool visible);

    ::krpc::Stream<UI::Text> add_text_stream(std::string content, bool visible);

    ::krpc::Stream<UI::RectTransform> rect_transform_stream();

    ::krpc::Stream<bool> visible_stream();
  };

  /**
   * A Unity engine Rect Transform for a UI object.
   * See the <a href="http://docs.unity3d.com/Manual/class-RectTransform.html">Unity manual</a> for more details.
   */
  class RectTransform : public krpc::Object<RectTransform> {
   public:
    explicit RectTransform(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Position of the rectangles upper right corner relative to the anchors.
     */
    std::tuple<double, double> upper_right();

    /**
     * Rotation, as a quaternion, of the object around its pivot point.
     */
    void set_rotation(std::tuple<double, double, double, double> value);

    /**
     * Position of the rectangles lower left corner relative to the anchors.
     */
    std::tuple<double, double> lower_left();

    /**
     * Position of the rectangles pivot point relative to the anchors.
     */
    void set_local_position(std::tuple<double, double, double> value);

    /**
     * Width and height of the rectangle.
     */
    void set_size(std::tuple<double, double> value);

    /**
     * Scale factor applied to the object in the x, y and z dimensions.
     */
    void set_scale(std::tuple<double, double, double> value);

    /**
     * Position of the rectangles pivot point relative to the anchors.
     */
    std::tuple<double, double, double> local_position();

    /**
     * Location of the pivot point around which the rectangle rotates, defined as a fraction of the size of the rectangle itself.
     */
    void set_pivot(std::tuple<double, double> value);

    /**
     * Position of the rectangles upper right corner relative to the anchors.
     */
    void set_upper_right(std::tuple<double, double> value);

    /**
     * The anchor point for the lower left corner of the rectangle defined as a fraction of the size of the parent rectangle.
     */
    std::tuple<double, double> anchor_max();

    /**
     * The anchor point for the upper right corner of the rectangle defined as a fraction of the size of the parent rectangle.
     */
    void set_anchor_min(std::tuple<double, double> value);

    /**
     * The anchor point for the upper right corner of the rectangle defined as a fraction of the size of the parent rectangle.
     */
    std::tuple<double, double> anchor_min();

    /**
     * The anchor point for the lower left corner of the rectangle defined as a fraction of the size of the parent rectangle.
     */
    void set_anchor_max(std::tuple<double, double> value);

    /**
     * Scale factor applied to the object in the x, y and z dimensions.
     */
    std::tuple<double, double, double> scale();

    /**
     * Position of the rectangles lower left corner relative to the anchors.
     */
    void set_lower_left(std::tuple<double, double> value);

    /**
     * Position of the rectangles pivot point relative to the anchors.
     */
    std::tuple<double, double> position();

    /**
     * Location of the pivot point around which the rectangle rotates, defined as a fraction of the size of the rectangle itself.
     */
    std::tuple<double, double> pivot();

    /**
     * Position of the rectangles pivot point relative to the anchors.
     */
    void set_position(std::tuple<double, double> value);

    /**
     * Rotation, as a quaternion, of the object around its pivot point.
     */
    std::tuple<double, double, double, double> rotation();

    /**
     * Set the minimum and maximum anchor points as a fraction of the size of the parent rectangle.
     */
    void set_anchor(std::tuple<double, double> value);

    /**
     * Width and height of the rectangle.
     */
    std::tuple<double, double> size();

    ::krpc::Stream<std::tuple<double, double>> upper_right_stream();

    ::krpc::Stream<std::tuple<double, double>> lower_left_stream();

    ::krpc::Stream<std::tuple<double, double, double>> local_position_stream();

    ::krpc::Stream<std::tuple<double, double>> anchor_max_stream();

    ::krpc::Stream<std::tuple<double, double>> anchor_min_stream();

    ::krpc::Stream<std::tuple<double, double, double>> scale_stream();

    ::krpc::Stream<std::tuple<double, double>> position_stream();

    ::krpc::Stream<std::tuple<double, double>> pivot_stream();

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream();

    ::krpc::Stream<std::tuple<double, double>> size_stream();
  };

  /**
   * A text label. See UI::Panel::add_text.
   */
  class Text : public krpc::Object<Text> {
   public:
    explicit Text(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the UI object.
     */
    void remove();

    /**
     * Name of the font
     */
    void set_font(std::string value);

    /**
     * Font size.
     */
    google::protobuf::int32 size();

    /**
     * Font style.
     */
    UI::FontStyle style();

    /**
     * Font style.
     */
    void set_style(UI::FontStyle value);

    /**
     * The text string
     */
    void set_content(std::string value);

    /**
     * Whether the UI object is visible.
     */
    bool visible();

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * The rect transform for the text.
     */
    UI::RectTransform rect_transform();

    /**
     * Line spacing.
     */
    void set_line_spacing(float value);

    /**
     * Whether the UI object is visible.
     */
    void set_visible(bool value);

    /**
     * The text string
     */
    std::string content();

    /**
     * Line spacing.
     */
    float line_spacing();

    /**
     * Font size.
     */
    void set_size(google::protobuf::int32 value);

    /**
     * A list of all available fonts.
     */
    std::vector<std::string> available_fonts();

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    /**
     * Name of the font
     */
    std::string font();

    /**
     * Alignment.
     */
    UI::TextAnchor alignment();

    /**
     * Alignment.
     */
    void set_alignment(UI::TextAnchor value);

    ::krpc::Stream<google::protobuf::int32> size_stream();

    ::krpc::Stream<UI::FontStyle> style_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<UI::RectTransform> rect_transform_stream();

    ::krpc::Stream<std::string> content_stream();

    ::krpc::Stream<float> line_spacing_stream();

    ::krpc::Stream<std::vector<std::string>> available_fonts_stream();

    ::krpc::Stream<std::string> font_stream();

    ::krpc::Stream<UI::TextAnchor> alignment_stream();
  };
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::UI::FontStyle& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::UI::MessagePosition& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::UI::TextAlignment& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::UI::TextAnchor& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::UI::FontStyle& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::UI::FontStyle>(x);
  }

  inline void decode(services::UI::MessagePosition& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::UI::MessagePosition>(x);
  }

  inline void decode(services::UI::TextAlignment& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::UI::TextAlignment>(x);
  }

  inline void decode(services::UI::TextAnchor& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::UI::TextAnchor>(x);
  }

}  // namespace decoder

namespace services {

inline UI::UI(Client* client):
  Service(client) {}

inline UI::Canvas UI::add_canvas() {
  std::string _data = this->_client->invoke("UI", "AddCanvas");
  UI::Canvas _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::clear(bool client_only = false) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(client_only));
  this->_client->invoke("UI", "Clear", _args);
}

inline void UI::message(std::string content, float duration = 1.0, UI::MessagePosition position = static_cast<UI::MessagePosition>(1)) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(duration));
  _args.push_back(encoder::encode(position));
  this->_client->invoke("UI", "Message", _args);
}

inline UI::Canvas UI::stock_canvas() {
  std::string _data = this->_client->invoke("UI", "get_StockCanvas");
  UI::Canvas _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<UI::Canvas> UI::add_canvas_stream() {
  return ::krpc::Stream<UI::Canvas>(this->_client, this->_client->request("UI", "AddCanvas"));
}

inline ::krpc::Stream<UI::Canvas> UI::stock_canvas_stream() {
  return ::krpc::Stream<UI::Canvas>(this->_client, this->_client->request("UI", "get_StockCanvas"));
}

inline UI::Button::Button(Client* client, google::protobuf::uint64 id):
  Object(client, "UI::Button", id) {}

inline void UI::Button::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("UI", "Button_Remove", _args);
}

inline bool UI::Button::clicked() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Button_get_Clicked", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Button::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Button_set_Visible", _args);
}

inline void UI::Button::set_clicked(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Button_set_Clicked", _args);
}

inline bool UI::Button::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Button_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::RectTransform UI::Button::rect_transform() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Button_get_RectTransform", _args);
  UI::RectTransform _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::Text UI::Button::text() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Button_get_Text", _args);
  UI::Text _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> UI::Button::clicked_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "Button_get_Clicked", _args));
}

inline ::krpc::Stream<bool> UI::Button::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "Button_get_Visible", _args));
}

inline ::krpc::Stream<UI::RectTransform> UI::Button::rect_transform_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::RectTransform>(this->_client, this->_client->request("UI", "Button_get_RectTransform", _args));
}

inline ::krpc::Stream<UI::Text> UI::Button::text_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::Text>(this->_client, this->_client->request("UI", "Button_get_Text", _args));
}

inline UI::Canvas::Canvas(Client* client, google::protobuf::uint64 id):
  Object(client, "UI::Canvas", id) {}

inline UI::Button UI::Canvas::add_button(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Canvas_AddButton", _args);
  UI::Button _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::InputField UI::Canvas::add_input_field(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Canvas_AddInputField", _args);
  UI::InputField _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::Panel UI::Canvas::add_panel(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Canvas_AddPanel", _args);
  UI::Panel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::Text UI::Canvas::add_text(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Canvas_AddText", _args);
  UI::Text _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Canvas::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("UI", "Canvas_Remove", _args);
}

inline void UI::Canvas::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Canvas_set_Visible", _args);
}

inline UI::RectTransform UI::Canvas::rect_transform() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Canvas_get_RectTransform", _args);
  UI::RectTransform _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool UI::Canvas::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Canvas_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<UI::Button> UI::Canvas::add_button_stream(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::Button>(this->_client, this->_client->request("UI", "Canvas_AddButton", _args));
}

inline ::krpc::Stream<UI::InputField> UI::Canvas::add_input_field_stream(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::InputField>(this->_client, this->_client->request("UI", "Canvas_AddInputField", _args));
}

inline ::krpc::Stream<UI::Panel> UI::Canvas::add_panel_stream(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::Panel>(this->_client, this->_client->request("UI", "Canvas_AddPanel", _args));
}

inline ::krpc::Stream<UI::Text> UI::Canvas::add_text_stream(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::Text>(this->_client, this->_client->request("UI", "Canvas_AddText", _args));
}

inline ::krpc::Stream<UI::RectTransform> UI::Canvas::rect_transform_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::RectTransform>(this->_client, this->_client->request("UI", "Canvas_get_RectTransform", _args));
}

inline ::krpc::Stream<bool> UI::Canvas::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "Canvas_get_Visible", _args));
}

inline UI::InputField::InputField(Client* client, google::protobuf::uint64 id):
  Object(client, "UI::InputField", id) {}

inline void UI::InputField::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("UI", "InputField_Remove", _args);
}

inline void UI::InputField::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "InputField_set_Visible", _args);
}

inline UI::RectTransform UI::InputField::rect_transform() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "InputField_get_RectTransform", _args);
  UI::RectTransform _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::InputField::set_changed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "InputField_set_Changed", _args);
}

inline bool UI::InputField::changed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "InputField_get_Changed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string UI::InputField::value() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "InputField_get_Value", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool UI::InputField::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "InputField_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::Text UI::InputField::text() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "InputField_get_Text", _args);
  UI::Text _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::InputField::set_value(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "InputField_set_Value", _args);
}

inline ::krpc::Stream<UI::RectTransform> UI::InputField::rect_transform_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::RectTransform>(this->_client, this->_client->request("UI", "InputField_get_RectTransform", _args));
}

inline ::krpc::Stream<bool> UI::InputField::changed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "InputField_get_Changed", _args));
}

inline ::krpc::Stream<std::string> UI::InputField::value_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("UI", "InputField_get_Value", _args));
}

inline ::krpc::Stream<bool> UI::InputField::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "InputField_get_Visible", _args));
}

inline ::krpc::Stream<UI::Text> UI::InputField::text_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::Text>(this->_client, this->_client->request("UI", "InputField_get_Text", _args));
}

inline UI::Panel::Panel(Client* client, google::protobuf::uint64 id):
  Object(client, "UI::Panel", id) {}

inline UI::Button UI::Panel::add_button(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Panel_AddButton", _args);
  UI::Button _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::InputField UI::Panel::add_input_field(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Panel_AddInputField", _args);
  UI::InputField _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::Panel UI::Panel::add_panel(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Panel_AddPanel", _args);
  UI::Panel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::Text UI::Panel::add_text(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("UI", "Panel_AddText", _args);
  UI::Text _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Panel::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("UI", "Panel_Remove", _args);
}

inline void UI::Panel::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Panel_set_Visible", _args);
}

inline UI::RectTransform UI::Panel::rect_transform() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Panel_get_RectTransform", _args);
  UI::RectTransform _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool UI::Panel::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Panel_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<UI::Button> UI::Panel::add_button_stream(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::Button>(this->_client, this->_client->request("UI", "Panel_AddButton", _args));
}

inline ::krpc::Stream<UI::InputField> UI::Panel::add_input_field_stream(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::InputField>(this->_client, this->_client->request("UI", "Panel_AddInputField", _args));
}

inline ::krpc::Stream<UI::Panel> UI::Panel::add_panel_stream(bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::Panel>(this->_client, this->_client->request("UI", "Panel_AddPanel", _args));
}

inline ::krpc::Stream<UI::Text> UI::Panel::add_text_stream(std::string content, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(content));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<UI::Text>(this->_client, this->_client->request("UI", "Panel_AddText", _args));
}

inline ::krpc::Stream<UI::RectTransform> UI::Panel::rect_transform_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::RectTransform>(this->_client, this->_client->request("UI", "Panel_get_RectTransform", _args));
}

inline ::krpc::Stream<bool> UI::Panel::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "Panel_get_Visible", _args));
}

inline UI::RectTransform::RectTransform(Client* client, google::protobuf::uint64 id):
  Object(client, "UI::RectTransform", id) {}

inline std::tuple<double, double> UI::RectTransform::upper_right() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_UpperRight", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_rotation(std::tuple<double, double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_Rotation", _args);
}

inline std::tuple<double, double> UI::RectTransform::lower_left() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_LowerLeft", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_local_position(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_LocalPosition", _args);
}

inline void UI::RectTransform::set_size(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_Size", _args);
}

inline void UI::RectTransform::set_scale(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_Scale", _args);
}

inline std::tuple<double, double, double> UI::RectTransform::local_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_LocalPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_pivot(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_Pivot", _args);
}

inline void UI::RectTransform::set_upper_right(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_UpperRight", _args);
}

inline std::tuple<double, double> UI::RectTransform::anchor_max() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_AnchorMax", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_anchor_min(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_AnchorMin", _args);
}

inline std::tuple<double, double> UI::RectTransform::anchor_min() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_AnchorMin", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_anchor_max(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_AnchorMax", _args);
}

inline std::tuple<double, double, double> UI::RectTransform::scale() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_Scale", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_lower_left(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_LowerLeft", _args);
}

inline std::tuple<double, double> UI::RectTransform::position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_Position", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double> UI::RectTransform::pivot() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_Pivot", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_position(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_Position", _args);
}

inline std::tuple<double, double, double, double> UI::RectTransform::rotation() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::RectTransform::set_anchor(std::tuple<double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "RectTransform_set_Anchor", _args);
}

inline std::tuple<double, double> UI::RectTransform::size() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "RectTransform_get_Size", _args);
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::upper_right_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_UpperRight", _args));
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::lower_left_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_LowerLeft", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> UI::RectTransform::local_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_LocalPosition", _args));
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::anchor_max_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_AnchorMax", _args));
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::anchor_min_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_AnchorMin", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> UI::RectTransform::scale_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_Scale", _args));
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_Position", _args));
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::pivot_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_Pivot", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> UI::RectTransform::rotation_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_Rotation", _args));
}

inline ::krpc::Stream<std::tuple<double, double>> UI::RectTransform::size_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->request("UI", "RectTransform_get_Size", _args));
}

inline UI::Text::Text(Client* client, google::protobuf::uint64 id):
  Object(client, "UI::Text", id) {}

inline void UI::Text::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("UI", "Text_Remove", _args);
}

inline void UI::Text::set_font(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Font", _args);
}

inline google::protobuf::int32 UI::Text::size() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Size", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::FontStyle UI::Text::style() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Style", _args);
  UI::FontStyle _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Text::set_style(UI::FontStyle value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Style", _args);
}

inline void UI::Text::set_content(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Content", _args);
}

inline bool UI::Text::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> UI::Text::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::RectTransform UI::Text::rect_transform() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_RectTransform", _args);
  UI::RectTransform _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Text::set_line_spacing(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_LineSpacing", _args);
}

inline void UI::Text::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Visible", _args);
}

inline std::string UI::Text::content() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Content", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float UI::Text::line_spacing() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_LineSpacing", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Text::set_size(google::protobuf::int32 value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Size", _args);
}

inline std::vector<std::string> UI::Text::available_fonts() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_AvailableFonts", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Text::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Color", _args);
}

inline std::string UI::Text::font() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Font", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::TextAnchor UI::Text::alignment() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("UI", "Text_get_Alignment", _args);
  UI::TextAnchor _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void UI::Text::set_alignment(UI::TextAnchor value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("UI", "Text_set_Alignment", _args);
}

inline ::krpc::Stream<google::protobuf::int32> UI::Text::size_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("UI", "Text_get_Size", _args));
}

inline ::krpc::Stream<UI::FontStyle> UI::Text::style_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::FontStyle>(this->_client, this->_client->request("UI", "Text_get_Style", _args));
}

inline ::krpc::Stream<bool> UI::Text::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("UI", "Text_get_Visible", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> UI::Text::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("UI", "Text_get_Color", _args));
}

inline ::krpc::Stream<UI::RectTransform> UI::Text::rect_transform_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::RectTransform>(this->_client, this->_client->request("UI", "Text_get_RectTransform", _args));
}

inline ::krpc::Stream<std::string> UI::Text::content_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("UI", "Text_get_Content", _args));
}

inline ::krpc::Stream<float> UI::Text::line_spacing_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("UI", "Text_get_LineSpacing", _args));
}

inline ::krpc::Stream<std::vector<std::string>> UI::Text::available_fonts_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("UI", "Text_get_AvailableFonts", _args));
}

inline ::krpc::Stream<std::string> UI::Text::font_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("UI", "Text_get_Font", _args));
}

inline ::krpc::Stream<UI::TextAnchor> UI::Text::alignment_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::TextAnchor>(this->_client, this->_client->request("UI", "Text_get_Alignment", _args));
}
}  // namespace services

}  // namespace krpc
