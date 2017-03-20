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

class KRPC : public Service {
 public:
  explicit KRPC(Client* client);

  /**
   * The game scene. See KRPC::current_game_scene.
   */
  enum struct GameScene {
    /**
     * The game scene showing the Kerbal Space Center buildings.
     */
    space_center = 0,
    /**
     * The game scene showing a vessel in flight (or on the launchpad/runway).
     */
    flight = 1,
    /**
     * The tracking station.
     */
    tracking_station = 2,
    /**
     * The Vehicle Assembly Building.
     */
    editor_vab = 3,
    /**
     * The Space Plane Hangar.
     */
    editor_sph = 4
  };

  /**
   * Add a streaming request and return its identifier.
   */
  google::protobuf::uint32 add_stream(krpc::schema::Request request);

  /**
   * Returns information on all services, procedures, classes, properties etc. provided by the server.
   * Can be used by client libraries to automatically create functionality such as stubs.
   */
  krpc::schema::Services get_services();

  /**
   * Returns some information about the server, such as the version.
   */
  krpc::schema::Status get_status();

  /**
   * Remove a streaming request.
   */
  void remove_stream(google::protobuf::uint32 id);

  /**
   * A list of RPC clients that are currently connected to the server.
   * Each entry in the list is a clients identifier, name and address.
   */
  std::vector<std::tuple<std::string, std::string, std::string> > clients();

  /**
   * Get the current game scene.
   */
  KRPC::GameScene current_game_scene();

  ::krpc::Stream<google::protobuf::uint32> add_stream_stream(krpc::schema::Request request);

  ::krpc::Stream<krpc::schema::Services> get_services_stream();

  ::krpc::Stream<krpc::schema::Status> get_status_stream();

  ::krpc::Stream<std::vector<std::tuple<std::string, std::string, std::string> >> clients_stream();

  ::krpc::Stream<KRPC::GameScene> current_game_scene_stream();
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::KRPC::GameScene& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::KRPC::GameScene& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::KRPC::GameScene>(x);
  }

}  // namespace decoder

namespace services {

inline KRPC::KRPC(Client* client):
  Service(client) {}

inline google::protobuf::uint32 KRPC::add_stream(krpc::schema::Request request) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(request));
  std::string _data = this->_client->invoke("KRPC", "AddStream", _args);
  google::protobuf::uint32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline krpc::schema::Services KRPC::get_services() {
  std::string _data = this->_client->invoke("KRPC", "GetServices");
  krpc::schema::Services _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline krpc::schema::Status KRPC::get_status() {
  std::string _data = this->_client->invoke("KRPC", "GetStatus");
  krpc::schema::Status _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KRPC::remove_stream(google::protobuf::uint32 id) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  this->_client->invoke("KRPC", "RemoveStream", _args);
}

inline std::vector<std::tuple<std::string, std::string, std::string> > KRPC::clients() {
  std::string _data = this->_client->invoke("KRPC", "get_Clients");
  std::vector<std::tuple<std::string, std::string, std::string> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline KRPC::GameScene KRPC::current_game_scene() {
  std::string _data = this->_client->invoke("KRPC", "get_CurrentGameScene");
  KRPC::GameScene _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<google::protobuf::uint32> KRPC::add_stream_stream(krpc::schema::Request request) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(request));
  return ::krpc::Stream<google::protobuf::uint32>(this->_client, this->_client->request("KRPC", "AddStream", _args));
}

inline ::krpc::Stream<krpc::schema::Services> KRPC::get_services_stream() {
  return ::krpc::Stream<krpc::schema::Services>(this->_client, this->_client->request("KRPC", "GetServices"));
}

inline ::krpc::Stream<krpc::schema::Status> KRPC::get_status_stream() {
  return ::krpc::Stream<krpc::schema::Status>(this->_client, this->_client->request("KRPC", "GetStatus"));
}

inline ::krpc::Stream<std::vector<std::tuple<std::string, std::string, std::string> >> KRPC::clients_stream() {
  return ::krpc::Stream<std::vector<std::tuple<std::string, std::string, std::string> >>(this->_client, this->_client->request("KRPC", "get_Clients"));
}

inline ::krpc::Stream<KRPC::GameScene> KRPC::current_game_scene_stream() {
  return ::krpc::Stream<KRPC::GameScene>(this->_client, this->_client->request("KRPC", "get_CurrentGameScene"));
}
}  // namespace services

}  // namespace krpc
