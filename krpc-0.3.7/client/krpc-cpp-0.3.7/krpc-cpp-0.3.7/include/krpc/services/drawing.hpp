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

class Drawing : public Service {
 public:
  explicit Drawing(Client* client);

  // Class forward declarations
  class Line;
  class Polygon;
  class Text;

  /**
   * Draw a direction vector in the scene, from the center of mass of the active vessel.
   * @param direction Direction to draw the line in.
   * @param referenceFrame Reference frame that the direction is in.
   * @param length The length of the line.
   * @param visible Whether the line is visible.
   */
  Drawing::Line add_direction(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length, bool visible);

  /**
   * Draw a line in the scene.
   * @param start Position of the start of the line.
   * @param end Position of the end of the line.
   * @param referenceFrame Reference frame that the positions are in.
   * @param visible Whether the line is visible.
   */
  Drawing::Line add_line(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  /**
   * Draw a polygon in the scene, defined by a list of vertices.
   * @param vertices Vertices of the polygon.
   * @param referenceFrame Reference frame that the vertices are in.
   * @param visible Whether the polygon is visible.
   */
  Drawing::Polygon add_polygon(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  /**
   * Draw text in the scene.
   * @param text The string to draw.
   * @param referenceFrame Reference frame that the text position is in.
   * @param position Position of the text.
   * @param rotation Rotation of the text, as a quaternion.
   * @param visible Whether the text is visible.
   */
  Drawing::Text add_text(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible);

  /**
   * Remove all objects being drawn.
   * @param clientOnly If true, only remove objects created by the calling client.
   */
  void clear(bool client_only);

  ::krpc::Stream<Drawing::Line> add_direction_stream(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length, bool visible);

  ::krpc::Stream<Drawing::Line> add_line_stream(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  ::krpc::Stream<Drawing::Polygon> add_polygon_stream(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  ::krpc::Stream<Drawing::Text> add_text_stream(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible);

  /**
   * A line. Created using Drawing::add_line.
   */
  class Line : public krpc::Object<Line> {
   public:
    explicit Line(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the object.
     */
    void remove();

    /**
     * Reference frame for the positions of the object.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * End position of the line.
     */
    std::tuple<double, double, double> end();

    /**
     * Reference frame for the positions of the object.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    std::string material();

    /**
     * Whether the object is visible.
     */
    bool visible();

    /**
     * Set the thickness
     */
    void set_thickness(float value);

    /**
     * Start position of the line.
     */
    std::tuple<double, double, double> start();

    /**
     * Set the thickness
     */
    float thickness();

    /**
     * Whether the object is visible.
     */
    void set_visible(bool value);

    /**
     * End position of the line.
     */
    void set_end(std::tuple<double, double, double> value);

    /**
     * Start position of the line.
     */
    void set_start(std::tuple<double, double, double> value);

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    void set_material(std::string value);

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> end_stream();

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<std::string> material_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::Stream<std::tuple<double, double, double>> start_stream();

    ::krpc::Stream<float> thickness_stream();
  };

  /**
   * A polygon. Created using Drawing::add_polygon.
   */
  class Polygon : public krpc::Object<Polygon> {
   public:
    explicit Polygon(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the object.
     */
    void remove();

    /**
     * Reference frame for the positions of the object.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    void set_material(std::string value);

    /**
     * Reference frame for the positions of the object.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    std::string material();

    /**
     * Set the thickness
     */
    void set_thickness(float value);

    /**
     * Vertices for the polygon.
     */
    void set_vertices(std::vector<std::tuple<double, double, double> > value);

    /**
     * Set the thickness
     */
    float thickness();

    /**
     * Whether the object is visible.
     */
    void set_visible(bool value);

    /**
     * Whether the object is visible.
     */
    bool visible();

    /**
     * Vertices for the polygon.
     */
    std::vector<std::tuple<double, double, double> > vertices();

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<std::string> material_stream();

    ::krpc::Stream<float> thickness_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::Stream<std::vector<std::tuple<double, double, double> >> vertices_stream();
  };

  /**
   * Text. Created using Drawing::add_text.
   */
  class Text : public krpc::Object<Text> {
   public:
    explicit Text(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the object.
     */
    void remove();

    /**
     * Font size.
     */
    google::protobuf::int32 size();

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * Whether the object is visible.
     */
    bool visible();

    /**
     * Font style.
     */
    void set_style(UI::FontStyle value);

    /**
     * Font size.
     */
    void set_size(google::protobuf::int32 value);

    /**
     * A list of all available fonts.
     */
    std::vector<std::string> available_fonts();

    /**
     * Position of the text.
     */
    void set_position(std::tuple<double, double, double> value);

    /**
     * Name of the font
     */
    std::string font();

    /**
     * Alignment.
     */
    UI::TextAlignment alignment();

    /**
     * The text string
     */
    void set_content(std::string value);

    /**
     * Font style.
     */
    UI::FontStyle style();

    /**
     * Character size.
     */
    void set_character_size(float value);

    /**
     * The text string
     */
    std::string content();

    /**
     * Line spacing.
     */
    float line_spacing();

    /**
     * Alignment.
     */
    void set_alignment(UI::TextAlignment value);

    /**
     * Reference frame for the positions of the object.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * Line spacing.
     */
    void set_line_spacing(float value);

    /**
     * Character size.
     */
    float character_size();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    std::string material();

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    /**
     * Rotation of the text as a quaternion.
     */
    std::tuple<double, double, double, double> rotation();

    /**
     * Anchor.
     */
    void set_anchor(UI::TextAnchor value);

    /**
     * Name of the font
     */
    void set_font(std::string value);

    /**
     * Rotation of the text as a quaternion.
     */
    void set_rotation(std::tuple<double, double, double, double> value);

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    void set_material(std::string value);

    /**
     * Reference frame for the positions of the object.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * Whether the object is visible.
     */
    void set_visible(bool value);

    /**
     * Position of the text.
     */
    std::tuple<double, double, double> position();

    /**
     * Anchor.
     */
    UI::TextAnchor anchor();

    ::krpc::Stream<google::protobuf::int32> size_stream();

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::Stream<std::vector<std::string>> available_fonts_stream();

    ::krpc::Stream<std::string> font_stream();

    ::krpc::Stream<UI::TextAlignment> alignment_stream();

    ::krpc::Stream<UI::FontStyle> style_stream();

    ::krpc::Stream<std::string> content_stream();

    ::krpc::Stream<float> line_spacing_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<float> character_size_stream();

    ::krpc::Stream<std::string> material_stream();

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream();

    ::krpc::Stream<std::tuple<double, double, double>> position_stream();

    ::krpc::Stream<UI::TextAnchor> anchor_stream();
  };
};

}  // namespace services

namespace services {

inline Drawing::Drawing(Client* client):
  Service(client) {}

inline Drawing::Line Drawing::add_direction(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length = 10.0, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(length));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddDirection", _args);
  Drawing::Line _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline Drawing::Line Drawing::add_line(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(start));
  _args.push_back(encoder::encode(end));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddLine", _args);
  Drawing::Line _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline Drawing::Polygon Drawing::add_polygon(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vertices));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddPolygon", _args);
  Drawing::Polygon _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline Drawing::Text Drawing::add_text(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(text));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddText", _args);
  Drawing::Text _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::clear(bool client_only = false) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(client_only));
  this->_client->invoke("Drawing", "Clear", _args);
}

inline ::krpc::Stream<Drawing::Line> Drawing::add_direction_stream(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length = 10.0, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(length));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Line>(this->_client, this->_client->request("Drawing", "AddDirection", _args));
}

inline ::krpc::Stream<Drawing::Line> Drawing::add_line_stream(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(start));
  _args.push_back(encoder::encode(end));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Line>(this->_client, this->_client->request("Drawing", "AddLine", _args));
}

inline ::krpc::Stream<Drawing::Polygon> Drawing::add_polygon_stream(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vertices));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Polygon>(this->_client, this->_client->request("Drawing", "AddPolygon", _args));
}

inline ::krpc::Stream<Drawing::Text> Drawing::add_text_stream(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(text));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Text>(this->_client, this->_client->request("Drawing", "AddText", _args));
}

inline Drawing::Line::Line(Client* client, google::protobuf::uint64 id):
  Object(client, "Drawing::Line", id) {}

inline void Drawing::Line::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("Drawing", "Line_Remove", _args);
}

inline SpaceCenter::ReferenceFrame Drawing::Line::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> Drawing::Line::end() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_End", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_ReferenceFrame", _args);
}

inline std::tuple<double, double, double> Drawing::Line::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string Drawing::Line::material() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Material", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool Drawing::Line::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_thickness(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Thickness", _args);
}

inline std::tuple<double, double, double> Drawing::Line::start() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Start", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float Drawing::Line::thickness() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Thickness", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Visible", _args);
}

inline void Drawing::Line::set_end(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_End", _args);
}

inline void Drawing::Line::set_start(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Start", _args);
}

inline void Drawing::Line::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Color", _args);
}

inline void Drawing::Line::set_material(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Material", _args);
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> Drawing::Line::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("Drawing", "Line_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Line::end_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("Drawing", "Line_get_End", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Line::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("Drawing", "Line_get_Color", _args));
}

inline ::krpc::Stream<std::string> Drawing::Line::material_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("Drawing", "Line_get_Material", _args));
}

inline ::krpc::Stream<bool> Drawing::Line::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("Drawing", "Line_get_Visible", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Line::start_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("Drawing", "Line_get_Start", _args));
}

inline ::krpc::Stream<float> Drawing::Line::thickness_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("Drawing", "Line_get_Thickness", _args));
}

inline Drawing::Polygon::Polygon(Client* client, google::protobuf::uint64 id):
  Object(client, "Drawing::Polygon", id) {}

inline void Drawing::Polygon::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("Drawing", "Polygon_Remove", _args);
}

inline SpaceCenter::ReferenceFrame Drawing::Polygon::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_material(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Material", _args);
}

inline void Drawing::Polygon::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_ReferenceFrame", _args);
}

inline std::tuple<double, double, double> Drawing::Polygon::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string Drawing::Polygon::material() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Material", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_thickness(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Thickness", _args);
}

inline void Drawing::Polygon::set_vertices(std::vector<std::tuple<double, double, double> > value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Vertices", _args);
}

inline float Drawing::Polygon::thickness() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Thickness", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Visible", _args);
}

inline bool Drawing::Polygon::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::tuple<double, double, double> > Drawing::Polygon::vertices() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Vertices", _args);
  std::vector<std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Color", _args);
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> Drawing::Polygon::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("Drawing", "Polygon_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Polygon::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("Drawing", "Polygon_get_Color", _args));
}

inline ::krpc::Stream<std::string> Drawing::Polygon::material_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("Drawing", "Polygon_get_Material", _args));
}

inline ::krpc::Stream<float> Drawing::Polygon::thickness_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("Drawing", "Polygon_get_Thickness", _args));
}

inline ::krpc::Stream<bool> Drawing::Polygon::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("Drawing", "Polygon_get_Visible", _args));
}

inline ::krpc::Stream<std::vector<std::tuple<double, double, double> >> Drawing::Polygon::vertices_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::tuple<double, double, double> >>(this->_client, this->_client->request("Drawing", "Polygon_get_Vertices", _args));
}

inline Drawing::Text::Text(Client* client, google::protobuf::uint64 id):
  Object(client, "Drawing::Text", id) {}

inline void Drawing::Text::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("Drawing", "Text_Remove", _args);
}

inline google::protobuf::int32 Drawing::Text::size() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Size", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> Drawing::Text::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool Drawing::Text::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_style(UI::FontStyle value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Style", _args);
}

inline void Drawing::Text::set_size(google::protobuf::int32 value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Size", _args);
}

inline std::vector<std::string> Drawing::Text::available_fonts() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_AvailableFonts", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_position(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Position", _args);
}

inline std::string Drawing::Text::font() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Font", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::TextAlignment Drawing::Text::alignment() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Alignment", _args);
  UI::TextAlignment _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_content(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Content", _args);
}

inline UI::FontStyle Drawing::Text::style() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Style", _args);
  UI::FontStyle _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_character_size(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_CharacterSize", _args);
}

inline std::string Drawing::Text::content() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Content", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float Drawing::Text::line_spacing() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_LineSpacing", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_alignment(UI::TextAlignment value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Alignment", _args);
}

inline SpaceCenter::ReferenceFrame Drawing::Text::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_line_spacing(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_LineSpacing", _args);
}

inline float Drawing::Text::character_size() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_CharacterSize", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string Drawing::Text::material() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Material", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Color", _args);
}

inline std::tuple<double, double, double, double> Drawing::Text::rotation() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_anchor(UI::TextAnchor value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Anchor", _args);
}

inline void Drawing::Text::set_font(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Font", _args);
}

inline void Drawing::Text::set_rotation(std::tuple<double, double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Rotation", _args);
}

inline void Drawing::Text::set_material(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Material", _args);
}

inline void Drawing::Text::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_ReferenceFrame", _args);
}

inline void Drawing::Text::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Visible", _args);
}

inline std::tuple<double, double, double> Drawing::Text::position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline UI::TextAnchor Drawing::Text::anchor() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Anchor", _args);
  UI::TextAnchor _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<google::protobuf::int32> Drawing::Text::size_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("Drawing", "Text_get_Size", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Text::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("Drawing", "Text_get_Color", _args));
}

inline ::krpc::Stream<bool> Drawing::Text::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("Drawing", "Text_get_Visible", _args));
}

inline ::krpc::Stream<std::vector<std::string>> Drawing::Text::available_fonts_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("Drawing", "Text_get_AvailableFonts", _args));
}

inline ::krpc::Stream<std::string> Drawing::Text::font_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("Drawing", "Text_get_Font", _args));
}

inline ::krpc::Stream<UI::TextAlignment> Drawing::Text::alignment_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::TextAlignment>(this->_client, this->_client->request("Drawing", "Text_get_Alignment", _args));
}

inline ::krpc::Stream<UI::FontStyle> Drawing::Text::style_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::FontStyle>(this->_client, this->_client->request("Drawing", "Text_get_Style", _args));
}

inline ::krpc::Stream<std::string> Drawing::Text::content_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("Drawing", "Text_get_Content", _args));
}

inline ::krpc::Stream<float> Drawing::Text::line_spacing_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("Drawing", "Text_get_LineSpacing", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> Drawing::Text::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("Drawing", "Text_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<float> Drawing::Text::character_size_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("Drawing", "Text_get_CharacterSize", _args));
}

inline ::krpc::Stream<std::string> Drawing::Text::material_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("Drawing", "Text_get_Material", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> Drawing::Text::rotation_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("Drawing", "Text_get_Rotation", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Text::position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("Drawing", "Text_get_Position", _args));
}

inline ::krpc::Stream<UI::TextAnchor> Drawing::Text::anchor_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::TextAnchor>(this->_client, this->_client->request("Drawing", "Text_get_Anchor", _args));
}
}  // namespace services

}  // namespace krpc
