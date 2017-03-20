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

class RemoteTech : public Service {
 public:
  explicit RemoteTech(Client* client);

  // Class forward declarations
  class Antenna;
  class Comms;

  /**
   * The type of object an antenna is targetting.
   * See RemoteTech::Antenna::target.
   */
  enum struct Target {
    /**
     * The active vessel.
     */
    active_vessel = 0,
    /**
     * A celestial body.
     */
    celestial_body = 1,
    /**
     * A ground station.
     */
    ground_station = 2,
    /**
     * A specific vessel.
     */
    vessel = 3,
    /**
     * No target.
     */
    none = 4
  };

  /**
   * Get the antenna object for a particular part.
   */
  RemoteTech::Antenna antenna(SpaceCenter::Part part);

  /**
   * Get a communications object, representing the communication capability of a particular vessel.
   */
  RemoteTech::Comms comms(SpaceCenter::Vessel vessel);

  /**
   * Whether RemoteTech is installed.
   */
  bool available();

  /**
   * The names of the ground stations.
   */
  std::vector<std::string> ground_stations();

  ::krpc::Stream<RemoteTech::Antenna> antenna_stream(SpaceCenter::Part part);

  ::krpc::Stream<RemoteTech::Comms> comms_stream(SpaceCenter::Vessel vessel);

  ::krpc::Stream<bool> available_stream();

  ::krpc::Stream<std::vector<std::string>> ground_stations_stream();

  /**
   * A RemoteTech antenna. Obtained by calling RemoteTech::Comms::antennas or  RemoteTech::antenna.
   */
  class Antenna : public krpc::Object<Antenna> {
   public:
    explicit Antenna(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The celestial body the antenna is targetting.
     */
    void set_target_body(SpaceCenter::CelestialBody value);

    /**
     * The object that the antenna is targetting.
     * This property can be used to set the target to RemoteTech::Target::none or RemoteTech::Target::active_vessel.
     * To set the target to a celestial body, ground station or vessel see RemoteTech::Antenna::target_body,
     * RemoteTech::Antenna::target_ground_station and RemoteTech::Antenna::target_vessel.
     */
    RemoteTech::Target target();

    /**
     * The celestial body the antenna is targetting.
     */
    SpaceCenter::CelestialBody target_body();

    /**
     * The object that the antenna is targetting.
     * This property can be used to set the target to RemoteTech::Target::none or RemoteTech::Target::active_vessel.
     * To set the target to a celestial body, ground station or vessel see RemoteTech::Antenna::target_body,
     * RemoteTech::Antenna::target_ground_station and RemoteTech::Antenna::target_vessel.
     */
    void set_target(RemoteTech::Target value);

    /**
     * Whether the antenna has a connection.
     */
    bool has_connection();

    /**
     * The vessel the antenna is targetting.
     */
    void set_target_vessel(SpaceCenter::Vessel value);

    /**
     * The ground station the antenna is targetting.
     */
    void set_target_ground_station(std::string value);

    /**
     * Get the part containing this antenna.
     */
    SpaceCenter::Part part();

    /**
     * The ground station the antenna is targetting.
     */
    std::string target_ground_station();

    /**
     * The vessel the antenna is targetting.
     */
    SpaceCenter::Vessel target_vessel();

    ::krpc::Stream<RemoteTech::Target> target_stream();

    ::krpc::Stream<SpaceCenter::CelestialBody> target_body_stream();

    ::krpc::Stream<bool> has_connection_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::string> target_ground_station_stream();

    ::krpc::Stream<SpaceCenter::Vessel> target_vessel_stream();
  };

  /**
   * Communications for a vessel.
   */
  class Comms : public krpc::Object<Comms> {
   public:
    explicit Comms(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The signal delay between the this vessel and another vessel, in seconds.
     * @param other
     */
    double signal_delay_to_vessel(SpaceCenter::Vessel other);

    /**
     * The shortest signal delay to the vessel, in seconds.
     */
    double signal_delay();

    /**
     * Whether the vessel has a connection to a ground station.
     */
    bool has_connection_to_ground_station();

    /**
     * Whether the vessel has a flight computer on board.
     */
    bool has_flight_computer();

    /**
     * Whether the vessel has any connection.
     */
    bool has_connection();

    /**
     * Get the vessel.
     */
    SpaceCenter::Vessel vessel();

    /**
     * The signal delay between the vessel and the closest ground station, in seconds.
     */
    double signal_delay_to_ground_station();

    /**
     * The antennas for this vessel.
     */
    std::vector<RemoteTech::Antenna> antennas();

    /**
     * Whether the vessel can be controlled locally.
     */
    bool has_local_control();

    ::krpc::Stream<double> signal_delay_to_vessel_stream(SpaceCenter::Vessel other);

    ::krpc::Stream<double> signal_delay_stream();

    ::krpc::Stream<bool> has_connection_to_ground_station_stream();

    ::krpc::Stream<bool> has_flight_computer_stream();

    ::krpc::Stream<bool> has_connection_stream();

    ::krpc::Stream<SpaceCenter::Vessel> vessel_stream();

    ::krpc::Stream<double> signal_delay_to_ground_station_stream();

    ::krpc::Stream<std::vector<RemoteTech::Antenna>> antennas_stream();

    ::krpc::Stream<bool> has_local_control_stream();
  };
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::RemoteTech::Target& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::RemoteTech::Target& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::RemoteTech::Target>(x);
  }

}  // namespace decoder

namespace services {

inline RemoteTech::RemoteTech(Client* client):
  Service(client) {}

inline RemoteTech::Antenna RemoteTech::antenna(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna", _args);
  RemoteTech::Antenna _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline RemoteTech::Comms RemoteTech::comms(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  std::string _data = this->_client->invoke("RemoteTech", "Comms", _args);
  RemoteTech::Comms _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool RemoteTech::available() {
  std::string _data = this->_client->invoke("RemoteTech", "get_Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> RemoteTech::ground_stations() {
  std::string _data = this->_client->invoke("RemoteTech", "get_GroundStations");
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<RemoteTech::Antenna> RemoteTech::antenna_stream(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  return ::krpc::Stream<RemoteTech::Antenna>(this->_client, this->_client->request("RemoteTech", "Antenna", _args));
}

inline ::krpc::Stream<RemoteTech::Comms> RemoteTech::comms_stream(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  return ::krpc::Stream<RemoteTech::Comms>(this->_client, this->_client->request("RemoteTech", "Comms", _args));
}

inline ::krpc::Stream<bool> RemoteTech::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->request("RemoteTech", "get_Available"));
}

inline ::krpc::Stream<std::vector<std::string>> RemoteTech::ground_stations_stream() {
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("RemoteTech", "get_GroundStations"));
}

inline RemoteTech::Antenna::Antenna(Client* client, google::protobuf::uint64 id):
  Object(client, "RemoteTech::Antenna", id) {}

inline void RemoteTech::Antenna::set_target_body(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("RemoteTech", "Antenna_set_TargetBody", _args);
}

inline RemoteTech::Target RemoteTech::Antenna::target() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna_get_Target", _args);
  RemoteTech::Target _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CelestialBody RemoteTech::Antenna::target_body() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna_get_TargetBody", _args);
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void RemoteTech::Antenna::set_target(RemoteTech::Target value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("RemoteTech", "Antenna_set_Target", _args);
}

inline bool RemoteTech::Antenna::has_connection() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna_get_HasConnection", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void RemoteTech::Antenna::set_target_vessel(SpaceCenter::Vessel value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("RemoteTech", "Antenna_set_TargetVessel", _args);
}

inline void RemoteTech::Antenna::set_target_ground_station(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("RemoteTech", "Antenna_set_TargetGroundStation", _args);
}

inline SpaceCenter::Part RemoteTech::Antenna::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string RemoteTech::Antenna::target_ground_station() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna_get_TargetGroundStation", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel RemoteTech::Antenna::target_vessel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Antenna_get_TargetVessel", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<RemoteTech::Target> RemoteTech::Antenna::target_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<RemoteTech::Target>(this->_client, this->_client->request("RemoteTech", "Antenna_get_Target", _args));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> RemoteTech::Antenna::target_body_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->request("RemoteTech", "Antenna_get_TargetBody", _args));
}

inline ::krpc::Stream<bool> RemoteTech::Antenna::has_connection_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("RemoteTech", "Antenna_get_HasConnection", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> RemoteTech::Antenna::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("RemoteTech", "Antenna_get_Part", _args));
}

inline ::krpc::Stream<std::string> RemoteTech::Antenna::target_ground_station_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("RemoteTech", "Antenna_get_TargetGroundStation", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> RemoteTech::Antenna::target_vessel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("RemoteTech", "Antenna_get_TargetVessel", _args));
}

inline RemoteTech::Comms::Comms(Client* client, google::protobuf::uint64 id):
  Object(client, "RemoteTech::Comms", id) {}

inline double RemoteTech::Comms::signal_delay_to_vessel(SpaceCenter::Vessel other) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(other));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_SignalDelayToVessel", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double RemoteTech::Comms::signal_delay() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_SignalDelay", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool RemoteTech::Comms::has_connection_to_ground_station() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_HasConnectionToGroundStation", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool RemoteTech::Comms::has_flight_computer() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_HasFlightComputer", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool RemoteTech::Comms::has_connection() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_HasConnection", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel RemoteTech::Comms::vessel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_Vessel", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double RemoteTech::Comms::signal_delay_to_ground_station() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_SignalDelayToGroundStation", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<RemoteTech::Antenna> RemoteTech::Comms::antennas() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_Antennas", _args);
  std::vector<RemoteTech::Antenna> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool RemoteTech::Comms::has_local_control() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("RemoteTech", "Comms_get_HasLocalControl", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<double> RemoteTech::Comms::signal_delay_to_vessel_stream(SpaceCenter::Vessel other) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(other));
  return ::krpc::Stream<double>(this->_client, this->_client->request("RemoteTech", "Comms_SignalDelayToVessel", _args));
}

inline ::krpc::Stream<double> RemoteTech::Comms::signal_delay_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("RemoteTech", "Comms_get_SignalDelay", _args));
}

inline ::krpc::Stream<bool> RemoteTech::Comms::has_connection_to_ground_station_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("RemoteTech", "Comms_get_HasConnectionToGroundStation", _args));
}

inline ::krpc::Stream<bool> RemoteTech::Comms::has_flight_computer_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("RemoteTech", "Comms_get_HasFlightComputer", _args));
}

inline ::krpc::Stream<bool> RemoteTech::Comms::has_connection_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("RemoteTech", "Comms_get_HasConnection", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> RemoteTech::Comms::vessel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("RemoteTech", "Comms_get_Vessel", _args));
}

inline ::krpc::Stream<double> RemoteTech::Comms::signal_delay_to_ground_station_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("RemoteTech", "Comms_get_SignalDelayToGroundStation", _args));
}

inline ::krpc::Stream<std::vector<RemoteTech::Antenna>> RemoteTech::Comms::antennas_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<RemoteTech::Antenna>>(this->_client, this->_client->request("RemoteTech", "Comms_get_Antennas", _args));
}

inline ::krpc::Stream<bool> RemoteTech::Comms::has_local_control_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("RemoteTech", "Comms_get_HasLocalControl", _args));
}
}  // namespace services

}  // namespace krpc
