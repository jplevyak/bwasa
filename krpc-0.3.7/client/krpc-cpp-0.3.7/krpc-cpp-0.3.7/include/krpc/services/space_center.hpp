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

class SpaceCenter : public Service {
 public:
  explicit SpaceCenter(Client* client);

  // Class forward declarations
  class AutoPilot;
  class Camera;
  class CargoBay;
  class CelestialBody;
  class Control;
  class ControlSurface;
  class Decoupler;
  class DockingPort;
  class Engine;
  class Experiment;
  class Fairing;
  class Flight;
  class Force;
  class Intake;
  class LandingGear;
  class LandingLeg;
  class LaunchClamp;
  class Light;
  class Module;
  class Node;
  class Orbit;
  class Parachute;
  class Part;
  class Parts;
  class Propellant;
  class RCS;
  class Radiator;
  class ReactionWheel;
  class ReferenceFrame;
  class Resource;
  class ResourceConverter;
  class ResourceHarvester;
  class ResourceTransfer;
  class Resources;
  class ScienceData;
  class ScienceSubject;
  class Sensor;
  class SolarPanel;
  class Thruster;
  class Vessel;
  class Waypoint;
  class WaypointManager;

  /**
   * See SpaceCenter::Camera::mode.
   */
  enum struct CameraMode {
    /**
     * The camera is showing the active vessel, in "auto" mode.
     */
    automatic = 0,
    /**
     * The camera is showing the active vessel, in "free" mode.
     */
    free = 1,
    /**
     * The camera is showing the active vessel, in "chase" mode.
     */
    chase = 2,
    /**
     * The camera is showing the active vessel, in "locked" mode.
     */
    locked = 3,
    /**
     * The camera is showing the active vessel, in "orbital" mode.
     */
    orbital = 4,
    /**
     * The Intra-Vehicular Activity view is being shown.
     */
    iva = 5,
    /**
     * The map view is being shown.
     */
    map = 6
  };

  /**
   * The state of a cargo bay. See SpaceCenter::CargoBay::state.
   */
  enum struct CargoBayState {
    /**
     * Cargo bay is fully open.
     */
    open = 0,
    /**
     * Cargo bay closed and locked.
     */
    closed = 1,
    /**
     * Cargo bay is opening.
     */
    opening = 2,
    /**
     * Cargo bay is closing.
     */
    closing = 3
  };

  /**
   * The state of a docking port. See SpaceCenter::DockingPort::state.
   */
  enum struct DockingPortState {
    /**
     * The docking port is ready to dock to another docking port.
     */
    ready = 0,
    /**
     * The docking port is docked to another docking port, or docked to
     * another part (from the VAB/SPH).
     */
    docked = 1,
    /**
     * The docking port is very close to another docking port,
     * but has not docked. It is using magnetic force to acquire a solid dock.
     */
    docking = 2,
    /**
     * The docking port has just been undocked from another docking port,
     * and is disabled until it moves away by a sufficient distance
     * (SpaceCenter::DockingPort::reengage_distance).
     */
    undocking = 3,
    /**
     * The docking port has a shield, and the shield is closed.
     */
    shielded = 4,
    /**
     * The docking ports shield is currently opening/closing.
     */
    moving = 5
  };

  /**
   * The state of a landing gear. See SpaceCenter::LandingGear::state.
   */
  enum struct LandingGearState {
    /**
     * Landing gear is fully deployed.
     */
    deployed = 0,
    /**
     * Landing gear is fully retracted.
     */
    retracted = 1,
    /**
     * Landing gear is being deployed.
     */
    deploying = 2,
    /**
     * Landing gear is being retracted.
     */
    retracting = 3,
    /**
     * Landing gear is broken.
     */
    broken = 4
  };

  /**
   * The state of a landing leg. See SpaceCenter::LandingLeg::state.
   */
  enum struct LandingLegState {
    /**
     * Landing leg is fully deployed.
     */
    deployed = 0,
    /**
     * Landing leg is fully retracted.
     */
    retracted = 1,
    /**
     * Landing leg is being deployed.
     */
    deploying = 2,
    /**
     * Landing leg is being retracted.
     */
    retracting = 3,
    /**
     * Landing leg is broken.
     */
    broken = 4
  };

  /**
   * The state of a parachute. See SpaceCenter::Parachute::state.
   */
  enum struct ParachuteState {
    /**
     * The parachute is still stowed, but ready to semi-deploy.
     */
    active = 0,
    /**
     * The parachute has been cut.
     */
    cut = 1,
    /**
     * The parachute is fully deployed.
     */
    deployed = 2,
    /**
     * The parachute has been deployed and is providing some drag,
     * but is not fully deployed yet.
     */
    semi_deployed = 3,
    /**
     * The parachute is safely tucked away inside its housing.
     */
    stowed = 4
  };

  /**
   * The state of a radiator. SpaceCenter::RadiatorState
   */
  enum struct RadiatorState {
    /**
     * Radiator is fully extended.
     */
    extended = 0,
    /**
     * Radiator is fully retracted.
     */
    retracted = 1,
    /**
     * Radiator is being extended.
     */
    extending = 2,
    /**
     * Radiator is being retracted.
     */
    retracting = 3,
    /**
     * Radiator is being broken.
     */
    broken = 4
  };

  /**
   * The state of a resource converter. See SpaceCenter::ResourceConverter::state.
   */
  enum struct ResourceConverterState {
    /**
     * Converter is running.
     */
    running = 0,
    /**
     * Converter is idle.
     */
    idle = 1,
    /**
     * Converter is missing a required resource.
     */
    missing_resource = 2,
    /**
     * No available storage for output resource.
     */
    storage_full = 3,
    /**
     * At preset resource capacity.
     */
    capacity = 4,
    /**
     * Unknown state. Possible with modified resource converters.
     * In this case, check SpaceCenter::ResourceConverter::status_info for more information.
     */
    unknown = 5
  };

  /**
   * The way in which a resource flows between parts. See SpaceCenter::Resources::flow_mode.
   */
  enum struct ResourceFlowMode {
    /**
     * The resource flows to any part in the vessel. For example, electric charge.
     */
    vessel = 0,
    /**
     * The resource flows from parts in the first stage, followed by the second,
     * and so on. For example, mono-propellant.
     */
    stage = 1,
    /**
     * The resource flows between adjacent parts within the vessel. For example,
     * liquid fuel or oxidizer.
     */
    adjacent = 2,
    /**
     * The resource does not flow. For example, solid fuel.
     */
    none = 3
  };

  /**
   * The state of a resource harvester. See SpaceCenter::ResourceHarvester::state.
   */
  enum struct ResourceHarvesterState {
    /**
     * The drill is deploying.
     */
    deploying = 0,
    /**
     * The drill is deployed and ready.
     */
    deployed = 1,
    /**
     * The drill is retracting.
     */
    retracting = 2,
    /**
     * The drill is retracted.
     */
    retracted = 3,
    /**
     * The drill is running.
     */
    active = 4
  };

  /**
   * The behavior of the SAS auto-pilot. See SpaceCenter::AutoPilot::sas_mode.
   */
  enum struct SASMode {
    /**
     * Stability assist mode. Dampen out any rotation.
     */
    stability_assist = 0,
    /**
     * Point in the burn direction of the next maneuver node.
     */
    maneuver = 1,
    /**
     * Point in the prograde direction.
     */
    prograde = 2,
    /**
     * Point in the retrograde direction.
     */
    retrograde = 3,
    /**
     * Point in the orbit normal direction.
     */
    normal = 4,
    /**
     * Point in the orbit anti-normal direction.
     */
    anti_normal = 5,
    /**
     * Point in the orbit radial direction.
     */
    radial = 6,
    /**
     * Point in the orbit anti-radial direction.
     */
    anti_radial = 7,
    /**
     * Point in the direction of the current target.
     */
    target = 8,
    /**
     * Point away from the current target.
     */
    anti_target = 9
  };

  /**
   * The state of a solar panel. See SpaceCenter::SolarPanel::state.
   */
  enum struct SolarPanelState {
    /**
     * Solar panel is fully extended.
     */
    extended = 0,
    /**
     * Solar panel is fully retracted.
     */
    retracted = 1,
    /**
     * Solar panel is being extended.
     */
    extending = 2,
    /**
     * Solar panel is being retracted.
     */
    retracting = 3,
    /**
     * Solar panel is broken.
     */
    broken = 4
  };

  /**
   * The mode of the speed reported in the navball.
   * See SpaceCenter::Control::speed_mode.
   */
  enum struct SpeedMode {
    /**
     * Speed is relative to the vessel's orbit.
     */
    orbit = 0,
    /**
     * Speed is relative to the surface of the body being orbited.
     */
    surface = 1,
    /**
     * Speed is relative to the current target.
     */
    target = 2
  };

  /**
   * The situation a vessel is in.
   * See SpaceCenter::Vessel::situation.
   */
  enum struct VesselSituation {
    /**
     * Vessel is awaiting launch.
     */
    pre_launch = 0,
    /**
     * Vessel is orbiting a body.
     */
    orbiting = 1,
    /**
     * Vessel is on a sub-orbital trajectory.
     */
    sub_orbital = 2,
    /**
     * Escaping.
     */
    escaping = 3,
    /**
     * Vessel is flying through an atmosphere.
     */
    flying = 4,
    /**
     * Vessel is landed on the surface of a body.
     */
    landed = 5,
    /**
     * Vessel has splashed down in an ocean.
     */
    splashed = 6,
    /**
     * Vessel is docked to another.
     */
    docked = 7
  };

  /**
   * The type of a vessel.
   * See SpaceCenter::Vessel::type.
   */
  enum struct VesselType {
    /**
     * Ship.
     */
    ship = 0,
    /**
     * Station.
     */
    station = 1,
    /**
     * Lander.
     */
    lander = 2,
    /**
     * Probe.
     */
    probe = 3,
    /**
     * Rover.
     */
    rover = 4,
    /**
     * Base.
     */
    base = 5,
    /**
     * Debris.
     */
    debris = 6
  };

  /**
   * The time warp mode.
   * Returned by SpaceCenter::WarpMode
   */
  enum struct WarpMode {
    /**
     * Time warp is active, and in regular "on-rails" mode.
     */
    rails = 0,
    /**
     * Time warp is active, and in physical time warp mode.
     */
    physics = 1,
    /**
     * Time warp is not active.
     */
    none = 2
  };

  /**
   * Returns true if regular "on-rails" time warp can be used, at the specified warp
   * factor. The maximum time warp rate is limited by various things,
   * including how close the active vessel is to a planet. See
   * <a href="http://wiki.kerbalspaceprogram.com/wiki/Time_warp">the KSP wiki</a> for details.
   * @param factor The warp factor to check.
   */
  bool can_rails_warp_at(google::protobuf::int32 factor);

  /**
   * Clears the current target.
   */
  void clear_target();

  /**
   * Launch a vessel.
   * @param craftDirectory Name of the directory in the current saves "Ships" directory, that contains the craft file. For example "VAB" or "SPH".
   * @param name Name of the vessel to launch. This is the name of the ".craft" file in the save directory, without the ".craft" file extension.
   * @param launchSite Name of the launch site. For example "LaunchPad" or "Runway".
   */
  void launch_vessel(std::string craft_directory, std::string name, std::string launch_site);

  /**
   * Launch a new vessel from the SPH onto the runway.
   * @param name Name of the vessel to launch.
   *
   * This is equivalent to calling SpaceCenter::launch_vessel with the craft directory set to "SPH" and the launch site set to "Runway".
   */
  void launch_vessel_from_sph(std::string name);

  /**
   * Launch a new vessel from the VAB onto the launchpad.
   * @param name Name of the vessel to launch.
   *
   * This is equivalent to calling SpaceCenter::launch_vessel with the craft directory set to "VAB" and the launch site set to "LaunchPad".
   */
  void launch_vessel_from_vab(std::string name);

  /**
   * Returns a list of vessels from the given craftDirectory that can be launched.
   * @param craftDirectory Name of the directory in the current saves "Ships" directory. For example "VAB" or "SPH".
   */
  std::vector<std::string> launchable_vessels(std::string craft_directory);

  /**
   * Load the game with the given name.
   * This will create a load a save file called name.sfs from the folder of the current save game.
   */
  void load(std::string name);

  /**
   * Load a quicksave.
   *
   * This is the same as calling SpaceCenter::load with the name "quicksave".
   */
  void quickload();

  /**
   * Save a quicksave.
   *
   * This is the same as calling SpaceCenter::save with the name "quicksave".
   */
  void quicksave();

  /**
   * Save the game with a given name.
   * This will create a save file called name.sfs in the folder of the current save game.
   */
  void save(std::string name);

  /**
   * Converts a direction vector from one reference frame to another.
   * @param direction Direction vector in reference frame from.
   * @param from The reference frame that the direction vector is in.
   * @param to The reference frame to covert the direction vector to.
   * @return The corresponding direction vector in reference frame to.
   */
  std::tuple<double, double, double> transform_direction(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  /**
   * Converts a position vector from one reference frame to another.
   * @param position Position vector in reference frame from.
   * @param from The reference frame that the position vector is in.
   * @param to The reference frame to covert the position vector to.
   * @return The corresponding position vector in reference frame to.
   */
  std::tuple<double, double, double> transform_position(std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  /**
   * Converts a rotation from one reference frame to another.
   * @param rotation Rotation in reference frame from.
   * @param from The reference frame that the rotation is in.
   * @param to The corresponding rotation in reference frame to.
   * @return The corresponding rotation in reference frame to.
   */
  std::tuple<double, double, double, double> transform_rotation(std::tuple<double, double, double, double> rotation, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  /**
   * Converts a velocity vector (acting at the specified position vector) from one
   * reference frame to another. The position vector is required to take the
   * relative angular velocity of the reference frames into account.
   * @param position Position vector in reference frame from.
   * @param velocity Velocity vector in reference frame from.
   * @param from The reference frame that the position and velocity vectors are in.
   * @param to The reference frame to covert the velocity vector to.
   * @return The corresponding velocity in reference frame to.
   */
  std::tuple<double, double, double> transform_velocity(std::tuple<double, double, double> position, std::tuple<double, double, double> velocity, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  /**
   * Uses time acceleration to warp forward to a time in the future, specified
   * by universal time ut. This call blocks until the desired
   * time is reached. Uses regular "on-rails" or physical time warp as appropriate.
   * For example, physical time warp is used when the active vessel is traveling
   * through an atmosphere. When using regular "on-rails" time warp, the warp
   * rate is limited by maxRailsRate, and when using physical
   * time warp, the warp rate is limited by maxPhysicsRate.
   * @param ut The universal time to warp to, in seconds.
   * @param maxRailsRate The maximum warp rate in regular "on-rails" time warp.
   * @param maxPhysicsRate The maximum warp rate in physical time warp.
   * @return When the time warp is complete.
   */
  void warp_to(double ut, float max_rails_rate, float max_physics_rate);

  /**
   * The currently targeted docking port.
   */
  void set_target_docking_port(SpaceCenter::DockingPort value);

  /**
   * The currently active vessel.
   */
  SpaceCenter::Vessel active_vessel();

  /**
   * The time warp rate, using regular "on-rails" time warp. A value between
   * 0 and 7 inclusive. 0 means no time warp. Returns 0 if physical time warp
   * is active.
   *
   * If requested time warp factor cannot be set, it will be set to the next
   * lowest possible value. For example, if the vessel is too close to a
   * planet. See <a href="http://wiki.kerbalspaceprogram.com/wiki/Time_warp">
   * the KSP wiki</a> for details.
   */
  google::protobuf::int32 rails_warp_factor();

  /**
   * The current time warp mode. Returns SpaceCenter::WarpMode::none if time
   * warp is not active, SpaceCenter::WarpMode::rails if regular "on-rails" time warp
   * is active, or SpaceCenter::WarpMode::physics if physical time warp is active.
   */
  SpaceCenter::WarpMode warp_mode();

  /**
   * The currently targeted vessel.
   */
  void set_target_vessel(SpaceCenter::Vessel value);

  /**
   * The waypoint manager.
   */
  SpaceCenter::WaypointManager waypoint_manager();

  /**
   * The currently targeted docking port.
   */
  SpaceCenter::DockingPort target_docking_port();

  /**
   * The current warp factor. This is the index of the rate at which time
   * is passing for either regular "on-rails" or physical time warp. Returns 0
   * if time warp is not active. When in on-rails time warp, this is equal to
   * SpaceCenter::rails_warp_factor, and in physics time warp, this is equal to
   * SpaceCenter::physics_warp_factor.
   */
  float warp_factor();

  /**
   * The physical time warp rate. A value between 0 and 3 inclusive. 0 means
   * no time warp. Returns 0 if regular "on-rails" time warp is active.
   */
  void set_physics_warp_factor(google::protobuf::int32 value);

  /**
   * A list of all the vessels in the game.
   */
  std::vector<SpaceCenter::Vessel> vessels();

  /**
   * The current maximum regular "on-rails" warp factor that can be set.
   * A value between 0 and 7 inclusive.  See
   * <a href="http://wiki.kerbalspaceprogram.com/wiki/Time_warp">the KSP wiki</a> for details.
   */
  google::protobuf::int32 maximum_rails_warp_factor();

  /**
   * An object that can be used to control the camera.
   */
  SpaceCenter::Camera camera();

  /**
   * Whether <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a> is installed.
   */
  bool far_available();

  /**
   * The currently targeted vessel.
   */
  SpaceCenter::Vessel target_vessel();

  /**
   * The currently targeted celestial body.
   */
  SpaceCenter::CelestialBody target_body();

  /**
   * The current warp rate. This is the rate at which time is passing for
   * either on-rails or physical time warp. For example, a value of 10 means
   * time is passing 10x faster than normal. Returns 1 if time warp is not
   * active.
   */
  float warp_rate();

  /**
   * The currently active vessel.
   */
  void set_active_vessel(SpaceCenter::Vessel value);

  /**
   * The physical time warp rate. A value between 0 and 3 inclusive. 0 means
   * no time warp. Returns 0 if regular "on-rails" time warp is active.
   */
  google::protobuf::int32 physics_warp_factor();

  /**
   * The currently targeted celestial body.
   */
  void set_target_body(SpaceCenter::CelestialBody value);

  /**
   * The value of the <a href="https://en.wikipedia.org/wiki/Gravitational_constant">gravitational constant</a>
   * G in N(m/kg)^2.
   */
  double g();

  /**
   * The current universal time in seconds.
   */
  double ut();

  /**
   * The time warp rate, using regular "on-rails" time warp. A value between
   * 0 and 7 inclusive. 0 means no time warp. Returns 0 if physical time warp
   * is active.
   *
   * If requested time warp factor cannot be set, it will be set to the next
   * lowest possible value. For example, if the vessel is too close to a
   * planet. See <a href="http://wiki.kerbalspaceprogram.com/wiki/Time_warp">
   * the KSP wiki</a> for details.
   */
  void set_rails_warp_factor(google::protobuf::int32 value);

  /**
   * A dictionary of all celestial bodies (planets, moons, etc.) in the game,
   * keyed by the name of the body.
   */
  std::map<std::string, SpaceCenter::CelestialBody> bodies();

  ::krpc::Stream<bool> can_rails_warp_at_stream(google::protobuf::int32 factor);

  ::krpc::Stream<std::vector<std::string>> launchable_vessels_stream(std::string craft_directory);

  ::krpc::Stream<std::tuple<double, double, double>> transform_direction_stream(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  ::krpc::Stream<std::tuple<double, double, double>> transform_position_stream(std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  ::krpc::Stream<std::tuple<double, double, double, double>> transform_rotation_stream(std::tuple<double, double, double, double> rotation, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  ::krpc::Stream<std::tuple<double, double, double>> transform_velocity_stream(std::tuple<double, double, double> position, std::tuple<double, double, double> velocity, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to);

  ::krpc::Stream<SpaceCenter::Vessel> active_vessel_stream();

  ::krpc::Stream<google::protobuf::int32> rails_warp_factor_stream();

  ::krpc::Stream<SpaceCenter::WarpMode> warp_mode_stream();

  ::krpc::Stream<SpaceCenter::WaypointManager> waypoint_manager_stream();

  ::krpc::Stream<SpaceCenter::DockingPort> target_docking_port_stream();

  ::krpc::Stream<float> warp_factor_stream();

  ::krpc::Stream<std::vector<SpaceCenter::Vessel>> vessels_stream();

  ::krpc::Stream<google::protobuf::int32> maximum_rails_warp_factor_stream();

  ::krpc::Stream<SpaceCenter::Camera> camera_stream();

  ::krpc::Stream<bool> far_available_stream();

  ::krpc::Stream<SpaceCenter::Vessel> target_vessel_stream();

  ::krpc::Stream<SpaceCenter::CelestialBody> target_body_stream();

  ::krpc::Stream<float> warp_rate_stream();

  ::krpc::Stream<google::protobuf::int32> physics_warp_factor_stream();

  ::krpc::Stream<double> g_stream();

  ::krpc::Stream<double> ut_stream();

  ::krpc::Stream<std::map<std::string, SpaceCenter::CelestialBody>> bodies_stream();

  /**
   * Provides basic auto-piloting utilities for a vessel.
   * Created by calling SpaceCenter::Vessel::auto_pilot.
   *
   * If a client engages the auto-pilot and then closes its connection to the server,
   * the auto-pilot will be disengaged and its target reference frame, direction and roll reset to default.
   */
  class AutoPilot : public krpc::Object<AutoPilot> {
   public:
    explicit AutoPilot(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Disengage the auto-pilot.
     */
    void disengage();

    /**
     * Engage the auto-pilot.
     */
    void engage();

    /**
     * Set target pitch and heading angles.
     * @param pitch Target pitch angle, in degrees between -90° and +90°.
     * @param heading Target heading angle, in degrees between 0° and 360°.
     */
    void target_pitch_and_heading(float pitch, float heading);

    /**
     * Blocks until the vessel is pointing in the target direction and has the target roll (if set).
     */
    void wait();

    /**
     * The error, in degrees, between the vessels current and target heading.
     * Returns zero if the auto-pilot has not been engaged.
     */
    float heading_error();

    /**
     * The target time to peak used to autotune the PID controllers.
     * A vector of three times, in seconds, for each of the pitch, roll and yaw axes.
     * Defaults to 3 seconds for each axis.
     */
    std::tuple<double, double, double> time_to_peak();

    /**
     * The angle at which the autopilot considers the vessel to be pointing close to the target.
     * This determines the midpoint of the target velocity attenuation function.
     * A vector of three angles, in degrees, one for each of the pitch, roll and yaw axes.
     * Defaults to 1° for each axis.
     */
    std::tuple<double, double, double> attenuation_angle();

    /**
     * The target overshoot percentage used to autotune the PID controllers.
     * A vector of three values, between 0 and 1, for each of the pitch, roll and yaw axes.
     * Defaults to 0.01 for each axis.
     */
    std::tuple<double, double, double> overshoot();

    /**
     * The target overshoot percentage used to autotune the PID controllers.
     * A vector of three values, between 0 and 1, for each of the pitch, roll and yaw axes.
     * Defaults to 0.01 for each axis.
     */
    void set_overshoot(std::tuple<double, double, double> value);

    /**
     * Direction vector corresponding to the target pitch and heading.
     */
    std::tuple<double, double, double> target_direction();

    /**
     * The target time to peak used to autotune the PID controllers.
     * A vector of three times, in seconds, for each of the pitch, roll and yaw axes.
     * Defaults to 3 seconds for each axis.
     */
    void set_time_to_peak(std::tuple<double, double, double> value);

    /**
     * The state of SAS.
     *
     * Equivalent to SpaceCenter::Control::sas
     */
    bool sas();

    /**
     * The target heading, in degrees, between 0° and 360°.
     */
    float target_heading();

    /**
     * The time the vessel should take to come to a stop pointing in the target direction.
     * This determines the angular acceleration used to decelerate the vessel.
     * A vector of three times, in seconds, one for each of the pitch, roll and yaw axes.
     * Defaults to 5 seconds for each axis.
     */
    void set_deceleration_time(std::tuple<double, double, double> value);

    /**
     * Gains for the yaw PID controller.
     *
     * When SpaceCenter::AutoPilot::auto_tune is true, these values are updated automatically, which will overwrite any manual changes.
     */
    std::tuple<double, double, double> yaw_pid_gains();

    /**
     * Gains for the roll PID controller.
     *
     * When SpaceCenter::AutoPilot::auto_tune is true, these values are updated automatically, which will overwrite any manual changes.
     */
    void set_roll_pid_gains(std::tuple<double, double, double> value);

    /**
     * Gains for the roll PID controller.
     *
     * When SpaceCenter::AutoPilot::auto_tune is true, these values are updated automatically, which will overwrite any manual changes.
     */
    std::tuple<double, double, double> roll_pid_gains();

    /**
     * The target pitch, in degrees, between -90° and +90°.
     */
    float target_pitch();

    /**
     * The threshold at which the autopilot will try to match the target roll angle, if any.
     * Defaults to 5 degrees.
     */
    void set_roll_threshold(double value);

    /**
     * The current SpaceCenter::SASMode.
     * These modes are equivalent to the mode buttons to the left of the navball that appear when SAS is enabled.
     *
     * Equivalent to SpaceCenter::Control::sas_mode
     */
    SpaceCenter::SASMode sas_mode();

    /**
     * The error, in degrees, between the vessels current and target roll.
     * Returns zero if the auto-pilot has not been engaged or no target roll is set.
     */
    float roll_error();

    /**
     * The target heading, in degrees, between 0° and 360°.
     */
    void set_target_heading(float value);

    /**
     * The reference frame for the target direction (SpaceCenter::AutoPilot::target_direction).
     *
     * An error will be thrown if this property is set to a reference frame that rotates with the vessel being controlled,
     * as it is impossible to rotate the vessel in such a reference frame.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The maximum amount of time that the vessel should need to come to a complete stop.
     * This determines the maximum angular velocity of the vessel.
     * A vector of three stopping times, in seconds, one for each of the pitch, roll and yaw axes.
     * Defaults to 0.5 seconds for each axis.
     */
    std::tuple<double, double, double> stopping_time();

    /**
     * Whether the rotation rate controllers PID parameters should be automatically tuned using the
     * vessels moment of inertia and available torque. Defaults to true.
     * See SpaceCenter::AutoPilot::time_to_peak and  SpaceCenter::AutoPilot::overshoot.
     */
    bool auto_tune();

    /**
     * The time the vessel should take to come to a stop pointing in the target direction.
     * This determines the angular acceleration used to decelerate the vessel.
     * A vector of three times, in seconds, one for each of the pitch, roll and yaw axes.
     * Defaults to 5 seconds for each axis.
     */
    std::tuple<double, double, double> deceleration_time();

    /**
     * Gains for the pitch PID controller.
     *
     * When SpaceCenter::AutoPilot::auto_tune is true, these values are updated automatically, which will overwrite any manual changes.
     */
    void set_pitch_pid_gains(std::tuple<double, double, double> value);

    /**
     * The target pitch, in degrees, between -90° and +90°.
     */
    void set_target_pitch(float value);

    /**
     * Gains for the yaw PID controller.
     *
     * When SpaceCenter::AutoPilot::auto_tune is true, these values are updated automatically, which will overwrite any manual changes.
     */
    void set_yaw_pid_gains(std::tuple<double, double, double> value);

    /**
     * The threshold at which the autopilot will try to match the target roll angle, if any.
     * Defaults to 5 degrees.
     */
    double roll_threshold();

    /**
     * The target roll, in degrees. NaN if no target roll is set.
     */
    void set_target_roll(float value);

    /**
     * The current SpaceCenter::SASMode.
     * These modes are equivalent to the mode buttons to the left of the navball that appear when SAS is enabled.
     *
     * Equivalent to SpaceCenter::Control::sas_mode
     */
    void set_sas_mode(SpaceCenter::SASMode value);

    /**
     * Direction vector corresponding to the target pitch and heading.
     */
    void set_target_direction(std::tuple<double, double, double> value);

    /**
     * The target roll, in degrees. NaN if no target roll is set.
     */
    float target_roll();

    /**
     * Gains for the pitch PID controller.
     *
     * When SpaceCenter::AutoPilot::auto_tune is true, these values are updated automatically, which will overwrite any manual changes.
     */
    std::tuple<double, double, double> pitch_pid_gains();

    /**
     * The reference frame for the target direction (SpaceCenter::AutoPilot::target_direction).
     *
     * An error will be thrown if this property is set to a reference frame that rotates with the vessel being controlled,
     * as it is impossible to rotate the vessel in such a reference frame.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * The error, in degrees, between the vessels current and target pitch.
     * Returns zero if the auto-pilot has not been engaged.
     */
    float pitch_error();

    /**
     * The maximum amount of time that the vessel should need to come to a complete stop.
     * This determines the maximum angular velocity of the vessel.
     * A vector of three stopping times, in seconds, one for each of the pitch, roll and yaw axes.
     * Defaults to 0.5 seconds for each axis.
     */
    void set_stopping_time(std::tuple<double, double, double> value);

    /**
     * Whether the rotation rate controllers PID parameters should be automatically tuned using the
     * vessels moment of inertia and available torque. Defaults to true.
     * See SpaceCenter::AutoPilot::time_to_peak and  SpaceCenter::AutoPilot::overshoot.
     */
    void set_auto_tune(bool value);

    /**
     * The angle at which the autopilot considers the vessel to be pointing close to the target.
     * This determines the midpoint of the target velocity attenuation function.
     * A vector of three angles, in degrees, one for each of the pitch, roll and yaw axes.
     * Defaults to 1° for each axis.
     */
    void set_attenuation_angle(std::tuple<double, double, double> value);

    /**
     * The state of SAS.
     *
     * Equivalent to SpaceCenter::Control::sas
     */
    void set_sas(bool value);

    /**
     * The error, in degrees, between the direction the ship has been asked
     * to point in and the direction it is pointing in. Returns zero if the auto-pilot
     * has not been engaged and SAS is not enabled or is in stability assist mode.
     */
    float error();

    ::krpc::Stream<float> heading_error_stream();

    ::krpc::Stream<std::tuple<double, double, double>> time_to_peak_stream();

    ::krpc::Stream<std::tuple<double, double, double>> attenuation_angle_stream();

    ::krpc::Stream<std::tuple<double, double, double>> overshoot_stream();

    ::krpc::Stream<std::tuple<double, double, double>> target_direction_stream();

    ::krpc::Stream<bool> sas_stream();

    ::krpc::Stream<float> target_heading_stream();

    ::krpc::Stream<std::tuple<double, double, double>> yaw_pid_gains_stream();

    ::krpc::Stream<std::tuple<double, double, double>> roll_pid_gains_stream();

    ::krpc::Stream<float> target_pitch_stream();

    ::krpc::Stream<SpaceCenter::SASMode> sas_mode_stream();

    ::krpc::Stream<float> roll_error_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> stopping_time_stream();

    ::krpc::Stream<bool> auto_tune_stream();

    ::krpc::Stream<std::tuple<double, double, double>> deceleration_time_stream();

    ::krpc::Stream<double> roll_threshold_stream();

    ::krpc::Stream<float> target_roll_stream();

    ::krpc::Stream<std::tuple<double, double, double>> pitch_pid_gains_stream();

    ::krpc::Stream<float> pitch_error_stream();

    ::krpc::Stream<float> error_stream();
  };

  /**
   * Controls the game's camera.
   * Obtained by calling SpaceCenter::camera.
   */
  class Camera : public krpc::Object<Camera> {
   public:
    explicit Camera(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The distance from the camera to the subject, in meters.
     * A value between SpaceCenter::Camera::min_distance and SpaceCenter::Camera::max_distance.
     */
    float distance();

    /**
     * In map mode, the celestial body that the camera is focussed on.
     * Returns null if the camera is not focussed on a celestial body.
     * Returns an error is the camera is not in map mode.
     */
    void set_focussed_body(SpaceCenter::CelestialBody value);

    /**
     * The heading of the camera, in degrees.
     */
    void set_heading(float value);

    /**
     * The current mode of the camera.
     */
    void set_mode(SpaceCenter::CameraMode value);

    /**
     * The pitch of the camera, in degrees.
     * A value between SpaceCenter::Camera::min_pitch and SpaceCenter::Camera::max_pitch
     */
    void set_pitch(float value);

    /**
     * In map mode, the maneuver node that the camera is focussed on.
     * Returns null if the camera is not focussed on a maneuver node.
     * Returns an error is the camera is not in map mode.
     */
    void set_focussed_node(SpaceCenter::Node value);

    /**
     * The maximum pitch of the camera.
     */
    float max_pitch();

    /**
     * The distance from the camera to the subject, in meters.
     * A value between SpaceCenter::Camera::min_distance and SpaceCenter::Camera::max_distance.
     */
    void set_distance(float value);

    /**
     * The minimum pitch of the camera.
     */
    float min_pitch();

    /**
     * Default distance from the camera to the subject, in meters.
     */
    float default_distance();

    /**
     * In map mode, the maneuver node that the camera is focussed on.
     * Returns null if the camera is not focussed on a maneuver node.
     * Returns an error is the camera is not in map mode.
     */
    SpaceCenter::Node focussed_node();

    /**
     * In map mode, the vessel that the camera is focussed on.
     * Returns null if the camera is not focussed on a vessel.
     * Returns an error is the camera is not in map mode.
     */
    void set_focussed_vessel(SpaceCenter::Vessel value);

    /**
     * The current mode of the camera.
     */
    SpaceCenter::CameraMode mode();

    /**
     * In map mode, the vessel that the camera is focussed on.
     * Returns null if the camera is not focussed on a vessel.
     * Returns an error is the camera is not in map mode.
     */
    SpaceCenter::Vessel focussed_vessel();

    /**
     * The pitch of the camera, in degrees.
     * A value between SpaceCenter::Camera::min_pitch and SpaceCenter::Camera::max_pitch
     */
    float pitch();

    /**
     * Maximum distance from the camera to the subject, in meters.
     */
    float max_distance();

    /**
     * In map mode, the celestial body that the camera is focussed on.
     * Returns null if the camera is not focussed on a celestial body.
     * Returns an error is the camera is not in map mode.
     */
    SpaceCenter::CelestialBody focussed_body();

    /**
     * The heading of the camera, in degrees.
     */
    float heading();

    /**
     * Minimum distance from the camera to the subject, in meters.
     */
    float min_distance();

    ::krpc::Stream<float> distance_stream();

    ::krpc::Stream<float> max_pitch_stream();

    ::krpc::Stream<float> min_pitch_stream();

    ::krpc::Stream<float> default_distance_stream();

    ::krpc::Stream<SpaceCenter::Node> focussed_node_stream();

    ::krpc::Stream<SpaceCenter::CameraMode> mode_stream();

    ::krpc::Stream<SpaceCenter::Vessel> focussed_vessel_stream();

    ::krpc::Stream<float> pitch_stream();

    ::krpc::Stream<float> max_distance_stream();

    ::krpc::Stream<SpaceCenter::CelestialBody> focussed_body_stream();

    ::krpc::Stream<float> heading_stream();

    ::krpc::Stream<float> min_distance_stream();
  };

  /**
   * A cargo bay. Obtained by calling SpaceCenter::Part::cargo_bay.
   */
  class CargoBay : public krpc::Object<CargoBay> {
   public:
    explicit CargoBay(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The part object for this cargo bay.
     */
    SpaceCenter::Part part();

    /**
     * Whether the cargo bay is open.
     */
    void set_open(bool value);

    /**
     * Whether the cargo bay is open.
     */
    bool open();

    /**
     * The state of the cargo bay.
     */
    SpaceCenter::CargoBayState state();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> open_stream();

    ::krpc::Stream<SpaceCenter::CargoBayState> state_stream();
  };

  /**
   * Represents a celestial body (such as a planet or moon).
   * See SpaceCenter::bodies.
   */
  class CelestialBody : public krpc::Object<CelestialBody> {
   public:
    explicit CelestialBody(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Returns the angular velocity of the body in the specified reference
     * frame. The magnitude of the vector is the rotational speed of the body, in
     * radians per second, and the direction of the vector indicates the axis of
     * rotation, using the right-hand rule.
     * @param referenceFrame
     */
    std::tuple<double, double, double> angular_velocity(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The height of the surface relative to mean sea level at the given position,
     * in meters. When over water, this is the height of the sea-bed and is therefore a
     * negative value.
     * @param latitude Latitude in degrees
     * @param longitude Longitude in degrees
     */
    double bedrock_height(double latitude, double longitude);

    /**
     * The position of the surface at the given latitude and longitude, in the given
     * reference frame. When over water, this is the position at the bottom of the sea-bed.
     * @param latitude Latitude in degrees
     * @param longitude Longitude in degrees
     * @param referenceFrame Reference frame for the returned position vector
     */
    std::tuple<double, double, double> bedrock_position(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The biomes at the given latitude and longitude, in degrees.
     */
    std::string biome_at(double latitude, double longitude);

    /**
     * Returns the direction in which the north pole of the celestial body is
     * pointing, as a unit vector, in the specified reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The position at mean sea level at the given latitude and longitude, in the given reference frame.
     * @param latitude Latitude in degrees
     * @param longitude Longitude in degrees
     * @param referenceFrame Reference frame for the returned position vector
     */
    std::tuple<double, double, double> msl_position(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the position vector of the center of the body in the specified reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the rotation of the body in the specified reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double, double> rotation(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The height of the surface relative to mean sea level at the given position,
     * in meters. When over water this is equal to 0.
     * @param latitude Latitude in degrees
     * @param longitude Longitude in degrees
     */
    double surface_height(double latitude, double longitude);

    /**
     * The position of the surface at the given latitude and longitude, in the given
     * reference frame. When over water, this is the position of the surface of the water.
     * @param latitude Latitude in degrees
     * @param longitude Longitude in degrees
     * @param referenceFrame Reference frame for the returned position vector
     */
    std::tuple<double, double, double> surface_position(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the velocity vector of the body in the specified reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> velocity(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The reference frame that is fixed relative to the celestial body.
     *
     * - The origin is at the center of the body.
     * - The axes rotate with the body.
     * - The x-axis points from the center of the body
     *   towards the intersection of the prime meridian and equator (the
     *   position at 0° longitude, 0° latitude).
     * - The y-axis points from the center of the body
     *   towards the north pole.
     * - The z-axis points from the center of the body
     *   towards the equator at 90°E longitude.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The altitude, in meters, above which a vessel is considered to be flying "high" when doing science.
     */
    float flying_high_altitude_threshold();

    /**
     * The name of the body.
     */
    std::string name();

    /**
     * The sidereal rotational period of the body, in seconds.
     */
    float rotational_period();

    /**
     * The equatorial radius of the body, in meters.
     */
    float equatorial_radius();

    /**
     * The altitude, in meters, above which a vessel is considered to be in "high" space when doing science.
     */
    float space_high_altitude_threshold();

    /**
     * The reference frame that is fixed relative to this celestial body, and
     * orientated in a fixed direction (it does not rotate with the body).
     *
     * - The origin is at the center of the body.
     * - The axes do not rotate.
     * - The x-axis points in an arbitrary direction through the
     *   equator.
     * - The y-axis points from the center of the body towards
     *   the north pole.
     * - The z-axis points in an arbitrary direction through the
     *   equator.
     */
    SpaceCenter::ReferenceFrame non_rotating_reference_frame();

    /**
     * The orbit of the body.
     */
    SpaceCenter::Orbit orbit();

    /**
     * The rotational speed of the body, in radians per second.
     */
    float rotational_speed();

    /**
     * The acceleration due to gravity at sea level (mean altitude) on the body, in m/s^2.
     */
    float surface_gravity();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Standard_gravitational_parameter">standard
     * gravitational parameter</a> of the body in m^3s^{-2}.
     */
    float gravitational_parameter();

    /**
     * The biomes present on this body.
     */
    std::set<std::string> biomes();

    /**
     * A list of celestial bodies that are in orbit around this celestial body.
     */
    std::vector<SpaceCenter::CelestialBody> satellites();

    /**
     * true if the body has an atmosphere.
     */
    bool has_atmosphere();

    /**
     * Gets the reference frame that is fixed relative to this celestial body, but
     * orientated with the body's orbital prograde/normal/radial directions.
     *
     * - The origin is at the center of the body.
     * - The axes rotate with the orbital prograde/normal/radial
     *   directions.
     * - The x-axis points in the orbital anti-radial direction.
     * - The y-axis points in the orbital prograde direction.
     * - The z-axis points in the orbital normal direction.
     */
    SpaceCenter::ReferenceFrame orbital_reference_frame();

    /**
     * The radius of the sphere of influence of the body, in meters.
     */
    float sphere_of_influence();

    /**
     * The mass of the body, in kilograms.
     */
    float mass();

    /**
     * The depth of the atmosphere, in meters.
     */
    float atmosphere_depth();

    /**
     * true if there is oxygen in the atmosphere, required for air-breathing engines.
     */
    bool has_atmospheric_oxygen();

    ::krpc::Stream<std::tuple<double, double, double>> angular_velocity_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<double> bedrock_height_stream(double latitude, double longitude);

    ::krpc::Stream<std::tuple<double, double, double>> bedrock_position_stream(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::string> biome_at_stream(double latitude, double longitude);

    ::krpc::Stream<std::tuple<double, double, double>> direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> msl_position_stream(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<double> surface_height_stream(double latitude, double longitude);

    ::krpc::Stream<std::tuple<double, double, double>> surface_position_stream(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> velocity_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<float> flying_high_altitude_threshold_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<float> rotational_period_stream();

    ::krpc::Stream<float> equatorial_radius_stream();

    ::krpc::Stream<float> space_high_altitude_threshold_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> non_rotating_reference_frame_stream();

    ::krpc::Stream<SpaceCenter::Orbit> orbit_stream();

    ::krpc::Stream<float> rotational_speed_stream();

    ::krpc::Stream<float> surface_gravity_stream();

    ::krpc::Stream<float> gravitational_parameter_stream();

    ::krpc::Stream<std::set<std::string>> biomes_stream();

    ::krpc::Stream<std::vector<SpaceCenter::CelestialBody>> satellites_stream();

    ::krpc::Stream<bool> has_atmosphere_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> orbital_reference_frame_stream();

    ::krpc::Stream<float> sphere_of_influence_stream();

    ::krpc::Stream<float> mass_stream();

    ::krpc::Stream<float> atmosphere_depth_stream();

    ::krpc::Stream<bool> has_atmospheric_oxygen_stream();
  };

  /**
   * Used to manipulate the controls of a vessel. This includes adjusting the
   * throttle, enabling/disabling systems such as SAS and RCS, or altering the
   * direction in which the vessel is pointing.
   * Obtained by calling SpaceCenter::Vessel::control.
   *
   * Control inputs (such as pitch, yaw and roll) are zeroed when all clients
   * that have set one or more of these inputs are no longer connected.
   */
  class Control : public krpc::Object<Control> {
   public:
    explicit Control(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Activates the next stage. Equivalent to pressing the space bar in-game.
     * @return A list of vessel objects that are jettisoned from the active vessel.
     */
    std::vector<SpaceCenter::Vessel> activate_next_stage();

    /**
     * Creates a maneuver node at the given universal time, and returns a
     * SpaceCenter::Node object that can be used to modify it.
     * Optionally sets the magnitude of the delta-v for the maneuver node
     * in the prograde, normal and radial directions.
     * @param ut Universal time of the maneuver node.
     * @param prograde Delta-v in the prograde direction.
     * @param normal Delta-v in the normal direction.
     * @param radial Delta-v in the radial direction.
     */
    SpaceCenter::Node add_node(double ut, float prograde, float normal, float radial);

    /**
     * Returns true if the given action group is enabled.
     * @param group A number between 0 and 9 inclusive,
     * or between 0 and 250 inclusive when the <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/67235-12oct3116-action-groups-extended-250-action-groups-in-flight-editing-now-kosremotetech">Extended Action Groups mod</a> is installed.
     */
    bool get_action_group(google::protobuf::uint32 group);

    /**
     * Remove all maneuver nodes.
     */
    void remove_nodes();

    /**
     * Sets the state of the given action group.
     * @param group A number between 0 and 9 inclusive,
     * or between 0 and 250 inclusive when the <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/67235-12oct3116-action-groups-extended-250-action-groups-in-flight-editing-now-kosremotetech">Extended Action Groups mod</a> is installed.
     * @param state
     */
    void set_action_group(google::protobuf::uint32 group, bool state);

    /**
     * Toggles the state of the given action group.
     * @param group A number between 0 and 9 inclusive,
     * or between 0 and 250 inclusive when the <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/67235-12oct3116-action-groups-extended-250-action-groups-in-flight-editing-now-kosremotetech">Extended Action Groups mod</a> is installed.
     */
    void toggle_action_group(google::protobuf::uint32 group);

    /**
     * The state of the right translational control.
     * A value between -1 and 1.
     * Equivalent to the j and l keys.
     */
    float right();

    /**
     * The state of the wheel brakes.
     */
    bool brakes();

    /**
     * The state of the yaw control.
     * A value between -1 and 1.
     * Equivalent to the a and d keys.
     */
    void set_yaw(float value);

    /**
     * The state of the up translational control.
     * A value between -1 and 1.
     * Equivalent to the i and k keys.
     */
    void set_up(float value);

    /**
     * The state of the up translational control.
     * A value between -1 and 1.
     * Equivalent to the i and k keys.
     */
    float up();

    /**
     * The state of the abort action group.
     */
    bool abort();

    /**
     * The current stage of the vessel. Corresponds to the stage number in
     * the in-game UI.
     */
    google::protobuf::int32 current_stage();

    /**
     * The state of the pitch control.
     * A value between -1 and 1.
     * Equivalent to the w and s keys.
     */
    float pitch();

    /**
     * The state of SAS.
     *
     * Equivalent to SpaceCenter::AutoPilot::sas
     */
    bool sas();

    /**
     * The state of the wheel brakes.
     */
    void set_brakes(bool value);

    /**
     * The state of the right translational control.
     * A value between -1 and 1.
     * Equivalent to the j and l keys.
     */
    void set_right(float value);

    /**
     * The state of the yaw control.
     * A value between -1 and 1.
     * Equivalent to the a and d keys.
     */
    float yaw();

    /**
     * The state of RCS.
     */
    bool rcs();

    /**
     * The state of the lights.
     */
    bool lights();

    /**
     * The current SpaceCenter::SASMode.
     * These modes are equivalent to the mode buttons to
     * the left of the navball that appear when SAS is enabled.
     *
     * Equivalent to SpaceCenter::AutoPilot::sas_mode
     */
    SpaceCenter::SASMode sas_mode();

    /**
     * The state of the forward translational control.
     * A value between -1 and 1.
     * Equivalent to the h and n keys.
     */
    float forward();

    /**
     * The state of the landing gear/legs.
     */
    void set_gear(bool value);

    /**
     * The state of the roll control.
     * A value between -1 and 1.
     * Equivalent to the q and e keys.
     */
    float roll();

    /**
     * The state of SAS.
     *
     * Equivalent to SpaceCenter::AutoPilot::sas
     */
    void set_sas(bool value);

    /**
     * The state of the landing gear/legs.
     */
    bool gear();

    /**
     * The state of the wheel throttle.
     * A value between -1 and 1.
     * A value of 1 rotates the wheels forwards, a value of -1 rotates
     * the wheels backwards.
     */
    void set_wheel_throttle(float value);

    /**
     * The state of the wheel steering.
     * A value between -1 and 1.
     * A value of 1 steers to the left, and a value of -1 steers to the right.
     */
    float wheel_steering();

    /**
     * The state of the wheel steering.
     * A value between -1 and 1.
     * A value of 1 steers to the left, and a value of -1 steers to the right.
     */
    void set_wheel_steering(float value);

    /**
     * The current SpaceCenter::SpeedMode of the navball.
     * This is the mode displayed next to the speed at the top of the navball.
     */
    void set_speed_mode(SpaceCenter::SpeedMode value);

    /**
     * The state of the throttle. A value between 0 and 1.
     */
    void set_throttle(float value);

    /**
     * Returns a list of all existing maneuver nodes, ordered by time from first to last.
     */
    std::vector<SpaceCenter::Node> nodes();

    /**
     * The current SpaceCenter::SASMode.
     * These modes are equivalent to the mode buttons to
     * the left of the navball that appear when SAS is enabled.
     *
     * Equivalent to SpaceCenter::AutoPilot::sas_mode
     */
    void set_sas_mode(SpaceCenter::SASMode value);

    /**
     * The state of the abort action group.
     */
    void set_abort(bool value);

    /**
     * The state of the throttle. A value between 0 and 1.
     */
    float throttle();

    /**
     * The state of the pitch control.
     * A value between -1 and 1.
     * Equivalent to the w and s keys.
     */
    void set_pitch(float value);

    /**
     * The state of the forward translational control.
     * A value between -1 and 1.
     * Equivalent to the h and n keys.
     */
    void set_forward(float value);

    /**
     * The state of the wheel throttle.
     * A value between -1 and 1.
     * A value of 1 rotates the wheels forwards, a value of -1 rotates
     * the wheels backwards.
     */
    float wheel_throttle();

    /**
     * The state of the lights.
     */
    void set_lights(bool value);

    /**
     * The state of the roll control.
     * A value between -1 and 1.
     * Equivalent to the q and e keys.
     */
    void set_roll(float value);

    /**
     * The state of RCS.
     */
    void set_rcs(bool value);

    /**
     * The current SpaceCenter::SpeedMode of the navball.
     * This is the mode displayed next to the speed at the top of the navball.
     */
    SpaceCenter::SpeedMode speed_mode();

    ::krpc::Stream<std::vector<SpaceCenter::Vessel>> activate_next_stage_stream();

    ::krpc::Stream<SpaceCenter::Node> add_node_stream(double ut, float prograde, float normal, float radial);

    ::krpc::Stream<bool> get_action_group_stream(google::protobuf::uint32 group);

    ::krpc::Stream<float> right_stream();

    ::krpc::Stream<bool> brakes_stream();

    ::krpc::Stream<float> up_stream();

    ::krpc::Stream<bool> abort_stream();

    ::krpc::Stream<google::protobuf::int32> current_stage_stream();

    ::krpc::Stream<float> pitch_stream();

    ::krpc::Stream<bool> sas_stream();

    ::krpc::Stream<float> yaw_stream();

    ::krpc::Stream<bool> rcs_stream();

    ::krpc::Stream<bool> lights_stream();

    ::krpc::Stream<SpaceCenter::SASMode> sas_mode_stream();

    ::krpc::Stream<float> forward_stream();

    ::krpc::Stream<float> roll_stream();

    ::krpc::Stream<bool> gear_stream();

    ::krpc::Stream<float> wheel_steering_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Node>> nodes_stream();

    ::krpc::Stream<float> throttle_stream();

    ::krpc::Stream<float> wheel_throttle_stream();

    ::krpc::Stream<SpaceCenter::SpeedMode> speed_mode_stream();
  };

  /**
   * An aerodynamic control surface. Obtained by calling SpaceCenter::Part::control_surface.
   */
  class ControlSurface : public krpc::Object<ControlSurface> {
   public:
    explicit ControlSurface(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the control surface has roll control enabled.
     */
    void set_roll_enabled(bool value);

    /**
     * Whether the control surface has been fully deployed.
     */
    void set_deployed(bool value);

    /**
     * Whether the control surface has roll control enabled.
     */
    bool roll_enabled();

    /**
     * Whether the control surface movement is inverted.
     */
    void set_inverted(bool value);

    /**
     * Whether the control surface has yaw control enabled.
     */
    void set_yaw_enabled(bool value);

    /**
     * Whether the control surface movement is inverted.
     */
    bool inverted();

    /**
     * The part object for this control surface.
     */
    SpaceCenter::Part part();

    /**
     * Whether the control surface has pitch control enabled.
     */
    void set_pitch_enabled(bool value);

    /**
     * The available torque in the positive pitch, roll and yaw axes and
     * negative pitch, roll and yaw axes of the vessel, in Newton meters.
     * These axes correspond to the coordinate axes of the SpaceCenter::Vessel::reference_frame.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_torque();

    /**
     * Surface area of the control surface in m^2.
     */
    float surface_area();

    /**
     * Whether the control surface has yaw control enabled.
     */
    bool yaw_enabled();

    /**
     * Whether the control surface has pitch control enabled.
     */
    bool pitch_enabled();

    /**
     * Whether the control surface has been fully deployed.
     */
    bool deployed();

    ::krpc::Stream<bool> roll_enabled_stream();

    ::krpc::Stream<bool> inverted_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_torque_stream();

    ::krpc::Stream<float> surface_area_stream();

    ::krpc::Stream<bool> yaw_enabled_stream();

    ::krpc::Stream<bool> pitch_enabled_stream();

    ::krpc::Stream<bool> deployed_stream();
  };

  /**
   * A decoupler. Obtained by calling SpaceCenter::Part::decoupler
   */
  class Decoupler : public krpc::Object<Decoupler> {
   public:
    explicit Decoupler(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Fires the decoupler. Returns the new vessel created when the decoupler fires.
     * Throws an exception if the decoupler has already fired.
     */
    SpaceCenter::Vessel decouple();

    /**
     * The part object for this decoupler.
     */
    SpaceCenter::Part part();

    /**
     * Whether the decoupler is enabled in the staging sequence.
     */
    bool staged();

    /**
     * The impulse that the decoupler imparts when it is fired, in Newton seconds.
     */
    float impulse();

    /**
     * Whether the decoupler has fired.
     */
    bool decoupled();

    ::krpc::Stream<SpaceCenter::Vessel> decouple_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> staged_stream();

    ::krpc::Stream<float> impulse_stream();

    ::krpc::Stream<bool> decoupled_stream();
  };

  /**
   * A docking port. Obtained by calling SpaceCenter::Part::docking_port
   */
  class DockingPort : public krpc::Object<DockingPort> {
   public:
    explicit DockingPort(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The direction that docking port points in, in the given reference frame.
     */
    std::tuple<double, double, double> direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The position of the docking port in the given reference frame.
     */
    std::tuple<double, double, double> position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The rotation of the docking port, in the given reference frame.
     */
    std::tuple<double, double, double, double> rotation(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Undocks the docking port and returns the new SpaceCenter::Vessel that is created.
     * This method can be called for either docking port in a docked pair.
     * Throws an exception if the docking port is not docked to anything.
     *
     * After undocking, the active vessel may change. See SpaceCenter::active_vessel.
     */
    SpaceCenter::Vessel undock();

    /**
     * The reference frame that is fixed relative to this docking port, and
     * oriented with the port.
     *
     * - The origin is at the position of the docking port.
     * - The axes rotate with the docking port.
     * - The x-axis points out to the right side of the docking port.
     * - The y-axis points in the direction the docking port is facing.
     * - The z-axis points out of the bottom off the docking port.
     *
     * This reference frame is not necessarily equivalent to the reference frame
     * for the part, returned by SpaceCenter::Part::reference_frame.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The state of the docking ports shield, if it has one.
     *
     * Returns true if the docking port has a shield, and the shield is
     * closed. Otherwise returns false. When set to true, the shield is
     * closed, and when set to false the shield is opened. If the docking
     * port does not have a shield, setting this attribute has no effect.
     */
    bool shielded();

    /**
     * The distance a docking port must move away when it undocks before it
     * becomes ready to dock with another port, in meters.
     */
    float reengage_distance();

    /**
     * Whether the docking port has a shield.
     */
    bool has_shield();

    /**
     * The state of the docking ports shield, if it has one.
     *
     * Returns true if the docking port has a shield, and the shield is
     * closed. Otherwise returns false. When set to true, the shield is
     * closed, and when set to false the shield is opened. If the docking
     * port does not have a shield, setting this attribute has no effect.
     */
    void set_shielded(bool value);

    /**
     * The part that this docking port is docked to. Returns null if this
     * docking port is not docked to anything.
     */
    SpaceCenter::Part docked_part();

    /**
     * The current state of the docking port.
     */
    SpaceCenter::DockingPortState state();

    /**
     * The part object for this docking port.
     */
    SpaceCenter::Part part();

    ::krpc::Stream<std::tuple<double, double, double>> direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::Vessel> undock_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<bool> shielded_stream();

    ::krpc::Stream<float> reengage_distance_stream();

    ::krpc::Stream<bool> has_shield_stream();

    ::krpc::Stream<SpaceCenter::Part> docked_part_stream();

    ::krpc::Stream<SpaceCenter::DockingPortState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();
  };

  /**
   * An engine, including ones of various types.
   * For example liquid fuelled gimballed engines, solid rocket boosters and jet engines.
   * Obtained by calling SpaceCenter::Part::engine.
   *
   * For RCS thrusters SpaceCenter::Part::rcs.
   */
  class Engine : public krpc::Object<Engine> {
   public:
    explicit Engine(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Toggle the current engine mode.
     */
    void toggle_mode();

    /**
     * Whether the engine has multiple modes of operation.
     */
    bool has_modes();

    /**
     * Whether the engines gimbal is locked in place. Setting this attribute has
     * no effect if the engine is not gimballed.
     */
    bool gimbal_locked();

    /**
     * The current amount of thrust being produced by the engine, in Newtons.
     */
    float thrust();

    /**
     * Whether the engine will automatically switch modes.
     */
    void set_auto_mode_switch(bool value);

    /**
     * Whether the engine has any fuel available.
     *
     * The engine must be activated for this property to update correctly.
     */
    bool has_fuel();

    /**
     * The current specific impulse of the engine, in seconds. Returns zero
     * if the engine is not active.
     */
    float specific_impulse();

    /**
     * The name of the current engine mode.
     */
    void set_mode(std::string value);

    /**
     * The amount of thrust, in Newtons, that would be produced by the engine
     * when activated and with its throttle set to 100%.
     * Returns zero if the engine does not have any fuel.
     * Takes the engine's current SpaceCenter::Engine::thrust_limit and atmospheric conditions into account.
     */
    float available_thrust();

    /**
     * The thrust limiter of the engine. A value between 0 and 1. Setting this
     * attribute may have no effect, for example the thrust limit for a solid
     * rocket booster cannot be changed in flight.
     */
    float thrust_limit();

    /**
     * Whether the engine can be shutdown once activated. For example, this is
     * true for liquid fueled rockets and false for solid rocket boosters.
     */
    bool can_shutdown();

    /**
     * Whether the SpaceCenter::Control::throttle affects the engine. For example,
     * this is true for liquid fueled rockets, and false for solid rocket
     * boosters.
     */
    bool throttle_locked();

    /**
     * The gimbal limiter of the engine. A value between 0 and 1.
     * Returns 0 if the gimbal is locked.
     */
    void set_gimbal_limit(float value);

    /**
     * The thrust limiter of the engine. A value between 0 and 1. Setting this
     * attribute may have no effect, for example the thrust limit for a solid
     * rocket booster cannot be changed in flight.
     */
    void set_thrust_limit(float value);

    /**
     * The maximum amount of thrust that can be produced by the engine in a
     * vacuum, in Newtons. This is the amount of thrust produced by the engine
     * when activated, SpaceCenter::Engine::thrust_limit is set to 100%, the main
     * vessel's throttle is set to 100% and the engine is in a vacuum.
     */
    float max_vacuum_thrust();

    /**
     * The range over which the gimbal can move, in degrees.
     * Returns 0 if the engine is not gimballed.
     */
    float gimbal_range();

    /**
     * The names of the propellants that the engine consumes.
     */
    std::vector<std::string> propellant_names();

    /**
     * Whether the engine can be restarted once shutdown. If the engine cannot be shutdown,
     * returns false. For example, this is true for liquid fueled rockets
     * and false for solid rocket boosters.
     */
    bool can_restart();

    /**
     * The part object for this engine.
     */
    SpaceCenter::Part part();

    /**
     * The components of the engine that generate thrust.
     *
     * For example, this corresponds to the rocket nozzel on a solid rocket booster,
     * or the individual nozzels on a RAPIER engine.
     * The overall thrust produced by the engine, as reported by SpaceCenter::Engine::available_thrust,
     * SpaceCenter::Engine::max_thrust and others, is the sum of the thrust generated by each thruster.
     */
    std::vector<SpaceCenter::Thruster> thrusters();

    /**
     * Whether the engine is active. Setting this attribute may have no effect,
     * depending on SpaceCenter::Engine::can_shutdown and SpaceCenter::Engine::can_restart.
     */
    bool active();

    /**
     * The propellants that the engine consumes.
     */
    std::vector<SpaceCenter::Propellant> propellants();

    /**
     * The available torque in the pitch, roll and yaw axes of the vessel, in Newton meters.
     * These axes correspond to the coordinate axes of the SpaceCenter::Vessel::reference_frame.
     * Returns zero if the engine is inactive, or not gimballed.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_torque();

    /**
     * The current throttle setting for the engine. A value between 0 and 1.
     * This is not necessarily the same as the vessel's main throttle
     * setting, as some engines take time to adjust their throttle
     * (such as jet engines).
     */
    float throttle();

    /**
     * The available modes for the engine.
     * A dictionary mapping mode names to SpaceCenter::Engine objects.
     */
    std::map<std::string, SpaceCenter::Engine> modes();

    /**
     * Whether the engine is active. Setting this attribute may have no effect,
     * depending on SpaceCenter::Engine::can_shutdown and SpaceCenter::Engine::can_restart.
     */
    void set_active(bool value);

    /**
     * The specific impulse of the engine at sea level on Kerbin, in seconds.
     */
    float kerbin_sea_level_specific_impulse();

    /**
     * The ratio of resources that the engine consumes. A dictionary mapping resource names
     * to the ratio at which they are consumed by the engine.
     *
     * For example, if the ratios are 0.6 for LiquidFuel and 0.4 for Oxidizer, then for every 0.6 units of
     * LiquidFuel that the engine burns, it will burn 0.4 units of Oxidizer.
     */
    std::map<std::string, float> propellant_ratios();

    /**
     * Whether the engine will automatically switch modes.
     */
    bool auto_mode_switch();

    /**
     * The name of the current engine mode.
     */
    std::string mode();

    /**
     * The vacuum specific impulse of the engine, in seconds.
     */
    float vacuum_specific_impulse();

    /**
     * The amount of thrust, in Newtons, that would be produced by the engine
     * when activated and fueled, with its throttle and throttle limiter set to 100%.
     */
    float max_thrust();

    /**
     * Whether the engine is gimballed.
     */
    bool gimballed();

    /**
     * The gimbal limiter of the engine. A value between 0 and 1.
     * Returns 0 if the gimbal is locked.
     */
    float gimbal_limit();

    /**
     * Whether the engines gimbal is locked in place. Setting this attribute has
     * no effect if the engine is not gimballed.
     */
    void set_gimbal_locked(bool value);

    ::krpc::Stream<bool> has_modes_stream();

    ::krpc::Stream<bool> gimbal_locked_stream();

    ::krpc::Stream<float> thrust_stream();

    ::krpc::Stream<bool> has_fuel_stream();

    ::krpc::Stream<float> specific_impulse_stream();

    ::krpc::Stream<float> available_thrust_stream();

    ::krpc::Stream<float> thrust_limit_stream();

    ::krpc::Stream<bool> can_shutdown_stream();

    ::krpc::Stream<bool> throttle_locked_stream();

    ::krpc::Stream<float> max_vacuum_thrust_stream();

    ::krpc::Stream<float> gimbal_range_stream();

    ::krpc::Stream<std::vector<std::string>> propellant_names_stream();

    ::krpc::Stream<bool> can_restart_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Thruster>> thrusters_stream();

    ::krpc::Stream<bool> active_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Propellant>> propellants_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_torque_stream();

    ::krpc::Stream<float> throttle_stream();

    ::krpc::Stream<std::map<std::string, SpaceCenter::Engine>> modes_stream();

    ::krpc::Stream<float> kerbin_sea_level_specific_impulse_stream();

    ::krpc::Stream<std::map<std::string, float>> propellant_ratios_stream();

    ::krpc::Stream<bool> auto_mode_switch_stream();

    ::krpc::Stream<std::string> mode_stream();

    ::krpc::Stream<float> vacuum_specific_impulse_stream();

    ::krpc::Stream<float> max_thrust_stream();

    ::krpc::Stream<bool> gimballed_stream();

    ::krpc::Stream<float> gimbal_limit_stream();
  };

  /**
   * Obtained by calling SpaceCenter::Part::experiment.
   */
  class Experiment : public krpc::Object<Experiment> {
   public:
    explicit Experiment(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Dump the experimental data contained by the experiment.
     */
    void dump();

    /**
     * Reset the experiment.
     */
    void reset();

    /**
     * Run the experiment.
     */
    void run();

    /**
     * Transmit all experimental data contained by this part.
     */
    void transmit();

    /**
     * Determines if the experiment is available given the current conditions.
     */
    bool available();

    /**
     * The name of the biome the experiment is currently in.
     */
    std::string biome();

    /**
     * Containing information on the corresponding specific science result for the current conditions.
     * Returns null if experiment is unavailable.
     */
    SpaceCenter::ScienceSubject science_subject();

    /**
     * Whether the experiment is inoperable.
     */
    bool inoperable();

    /**
     * The part object for this experiment.
     */
    SpaceCenter::Part part();

    /**
     * Whether the experiment can be re-run.
     */
    bool rerunnable();

    /**
     * The data contained in this experiment.
     */
    std::vector<SpaceCenter::ScienceData> data();

    /**
     * Whether the experiment has been deployed.
     */
    bool deployed();

    /**
     * Whether the experiment contains data.
     */
    bool has_data();

    ::krpc::Stream<bool> available_stream();

    ::krpc::Stream<std::string> biome_stream();

    ::krpc::Stream<SpaceCenter::ScienceSubject> science_subject_stream();

    ::krpc::Stream<bool> inoperable_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> rerunnable_stream();

    ::krpc::Stream<std::vector<SpaceCenter::ScienceData>> data_stream();

    ::krpc::Stream<bool> deployed_stream();

    ::krpc::Stream<bool> has_data_stream();
  };

  /**
   * A fairing. Obtained by calling SpaceCenter::Part::fairing.
   */
  class Fairing : public krpc::Object<Fairing> {
   public:
    explicit Fairing(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Jettison the fairing. Has no effect if it has already been jettisoned.
     */
    void jettison();

    /**
     * The part object for this fairing.
     */
    SpaceCenter::Part part();

    /**
     * Whether the fairing has been jettisoned.
     */
    bool jettisoned();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> jettisoned_stream();
  };

  /**
   * Used to get flight telemetry for a vessel, by calling SpaceCenter::Vessel::flight.
   * All of the information returned by this class is given in the reference frame
   * passed to that method.
   * Obtained by calling SpaceCenter::Vessel::flight.
   *
   * To get orbital information, such as the apoapsis or inclination, see SpaceCenter::Orbit.
   */
  class Flight : public krpc::Object<Flight> {
   public:
    explicit Flight(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The current G force acting on the vessel in m/s^2.
     */
    float g_force();

    /**
     * The vessels Reynolds number.
     *
     * Requires <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a>.
     */
    float reynolds_number();

    /**
     * The <a href="https://en.wikipedia.org/wiki/True_airspeed">true air speed</a> of the vessel, in m/s.
     */
    float true_air_speed();

    /**
     * The static atmospheric pressure at mean sea level, in Pascals.
     */
    float static_pressure_at_msl();

    /**
     * Gets the <a href="https://en.wikipedia.org/wiki/Ballistic_coefficient">ballistic coefficient</a>.
     *
     * Requires <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a>.
     */
    float ballistic_coefficient();

    /**
     * The pitch angle of the vessel relative to the horizon, in degrees. A value between -90° and +90°.
     */
    float pitch();

    /**
     * The unit direction vector pointing in the prograde direction.
     */
    std::tuple<double, double, double> prograde();

    /**
     * The speed of the vessel in meters per second.
     */
    double speed();

    /**
     * Gets the coefficient of drag. This is the amount of drag produced by the vessel. It depends on air speed,
     * air density and wing area.
     *
     * Requires <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a>.
     */
    float drag_coefficient();

    /**
     * Gets the yaw angle between the orientation of the vessel and its velocity vector, in degrees.
     */
    float sideslip_angle();

    /**
     * The altitude above sea level, in meters.
     * Measured from the center of mass of the vessel.
     */
    double mean_altitude();

    /**
     * The speed of sound, in the atmosphere around the vessel, in m/s.
     */
    float speed_of_sound();

    /**
     * The velocity vector of the vessel. The magnitude of the vector is the speed of the vessel in meters per second.
     * The direction of the vector is the direction of the vessels motion.
     */
    std::tuple<double, double, double> velocity();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Total_air_temperature">total air temperature</a> of the atmosphere
     * around the vessel, in Kelvin. This temperature includes the SpaceCenter::Flight::static_air_temperature and the vessel's kinetic energy.
     */
    float total_air_temperature();

    /**
     * The unit direction vector pointing in the anti-normal direction.
     */
    std::tuple<double, double, double> anti_normal();

    /**
     * The altitude above the surface of the body or sea level, whichever is closer, in meters.
     * Measured from the center of mass of the vessel.
     */
    double surface_altitude();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Latitude">latitude</a> of the vessel for the body being orbited, in degrees.
     */
    double latitude();

    /**
     * The position of the center of mass of the vessel.
     */
    std::tuple<double, double, double> center_of_mass();

    /**
     * The current density of the atmosphere around the vessel, in kg/m^3.
     */
    float atmosphere_density();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Equivalent_airspeed">equivalent air speed</a> of the vessel, in m/s.
     */
    float equivalent_air_speed();

    /**
     * The altitude above the surface of the body, in meters. When over water, this is the altitude above the sea floor.
     * Measured from the center of mass of the vessel.
     */
    double bedrock_altitude();

    /**
     * The vertical speed of the vessel in meters per second.
     */
    double vertical_speed();

    /**
     * Gets the pitch angle between the orientation of the vessel and its velocity vector, in degrees.
     */
    float angle_of_attack();

    /**
     * The direction vector that the vessel is pointing in.
     */
    std::tuple<double, double, double> direction();

    /**
     * The elevation of the terrain under the vessel, in meters. This is the height of the terrain above sea level,
     * and is negative when the vessel is over the sea.
     */
    double elevation();

    /**
     * The unit direction vector pointing in the normal direction.
     */
    std::tuple<double, double, double> normal();

    /**
     * The horizontal speed of the vessel in meters per second.
     */
    double horizontal_speed();

    /**
     * The unit direction vector pointing in the retrograde direction.
     */
    std::tuple<double, double, double> retrograde();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Aerodynamic_force">aerodynamic drag</a> currently acting on the vessel,
     * as a vector pointing in the direction of the force, with its magnitude equal to the strength of the force in Newtons.
     */
    std::tuple<double, double, double> drag();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Aerodynamic_force">aerodynamic lift</a> currently acting on the vessel,
     * as a vector pointing in the direction of the force, with its magnitude equal to the strength of the force in Newtons.
     */
    std::tuple<double, double, double> lift();

    /**
     * Gets the current amount of stall, between 0 and 1. A value greater than 0.005 indicates a minor stall
     * and a value greater than 0.5 indicates a large-scale stall.
     *
     * Requires <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a>.
     */
    float stall_fraction();

    /**
     * An estimate of the current terminal velocity of the vessel, in m/s.
     * This is the speed at which the drag forces cancel out the force of gravity.
     */
    float terminal_velocity();

    /**
     * Gets the coefficient of lift. This is the amount of lift produced by the vessel, and depends on air speed, air density and wing area.
     *
     * Requires <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a>.
     */
    float lift_coefficient();

    /**
     * The rotation of the vessel.
     */
    std::tuple<double, double, double, double> rotation();

    /**
     * Gets the thrust specific fuel consumption for the jet engines on the vessel. This is a measure of the
     * efficiency of the engines, with a lower value indicating a more efficient vessel. This value is the
     * number of Newtons of fuel that are burned, per hour, to produce one newton of thrust.
     *
     * Requires <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/19321-105-ferram-aerospace-research-v01557-johnson-21816/">Ferram Aerospace Research</a>.
     */
    float thrust_specific_fuel_consumption();

    /**
     * The speed of the vessel, in multiples of the speed of sound.
     */
    float mach();

    /**
     * The dynamic pressure acting on the vessel, in Pascals. This is a measure of the strength of the
     * aerodynamic forces. It is equal to \frac{1}{2} . \mbox{air density} .  \mbox{velocity}^2.
     * It is commonly denoted Q.
     */
    float dynamic_pressure();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Longitude">longitude</a> of the vessel for the body being orbited, in degrees.
     */
    double longitude();

    /**
     * The roll angle of the vessel relative to the horizon, in degrees. A value between -180° and +180°.
     */
    float roll();

    /**
     * The total aerodynamic forces acting on the vessel, as a vector pointing in the direction of the force, with its
     * magnitude equal to the strength of the force in Newtons.
     */
    std::tuple<double, double, double> aerodynamic_force();

    /**
     * The unit direction vector pointing in the radial direction.
     */
    std::tuple<double, double, double> radial();

    /**
     * The unit direction vector pointing in the anti-radial direction.
     */
    std::tuple<double, double, double> anti_radial();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Total_air_temperature">static (ambient) temperature</a> of the
     * atmosphere around the vessel, in Kelvin.
     */
    float static_air_temperature();

    /**
     * The heading angle of the vessel relative to north, in degrees. A value between 0° and 360°.
     */
    float heading();

    /**
     * The static atmospheric pressure acting on the vessel, in Pascals.
     */
    float static_pressure();

    ::krpc::Stream<float> g_force_stream();

    ::krpc::Stream<float> reynolds_number_stream();

    ::krpc::Stream<float> true_air_speed_stream();

    ::krpc::Stream<float> static_pressure_at_msl_stream();

    ::krpc::Stream<float> ballistic_coefficient_stream();

    ::krpc::Stream<float> pitch_stream();

    ::krpc::Stream<std::tuple<double, double, double>> prograde_stream();

    ::krpc::Stream<double> speed_stream();

    ::krpc::Stream<float> drag_coefficient_stream();

    ::krpc::Stream<float> sideslip_angle_stream();

    ::krpc::Stream<double> mean_altitude_stream();

    ::krpc::Stream<float> speed_of_sound_stream();

    ::krpc::Stream<std::tuple<double, double, double>> velocity_stream();

    ::krpc::Stream<float> total_air_temperature_stream();

    ::krpc::Stream<std::tuple<double, double, double>> anti_normal_stream();

    ::krpc::Stream<double> surface_altitude_stream();

    ::krpc::Stream<double> latitude_stream();

    ::krpc::Stream<std::tuple<double, double, double>> center_of_mass_stream();

    ::krpc::Stream<float> atmosphere_density_stream();

    ::krpc::Stream<float> equivalent_air_speed_stream();

    ::krpc::Stream<double> bedrock_altitude_stream();

    ::krpc::Stream<double> vertical_speed_stream();

    ::krpc::Stream<float> angle_of_attack_stream();

    ::krpc::Stream<std::tuple<double, double, double>> direction_stream();

    ::krpc::Stream<double> elevation_stream();

    ::krpc::Stream<std::tuple<double, double, double>> normal_stream();

    ::krpc::Stream<double> horizontal_speed_stream();

    ::krpc::Stream<std::tuple<double, double, double>> retrograde_stream();

    ::krpc::Stream<std::tuple<double, double, double>> drag_stream();

    ::krpc::Stream<std::tuple<double, double, double>> lift_stream();

    ::krpc::Stream<float> stall_fraction_stream();

    ::krpc::Stream<float> terminal_velocity_stream();

    ::krpc::Stream<float> lift_coefficient_stream();

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream();

    ::krpc::Stream<float> thrust_specific_fuel_consumption_stream();

    ::krpc::Stream<float> mach_stream();

    ::krpc::Stream<float> dynamic_pressure_stream();

    ::krpc::Stream<double> longitude_stream();

    ::krpc::Stream<float> roll_stream();

    ::krpc::Stream<std::tuple<double, double, double>> aerodynamic_force_stream();

    ::krpc::Stream<std::tuple<double, double, double>> radial_stream();

    ::krpc::Stream<std::tuple<double, double, double>> anti_radial_stream();

    ::krpc::Stream<float> static_air_temperature_stream();

    ::krpc::Stream<float> heading_stream();

    ::krpc::Stream<float> static_pressure_stream();
  };

  /**
   * Obtained by calling SpaceCenter::Part::add_force.
   */
  class Force : public krpc::Object<Force> {
   public:
    explicit Force(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Remove the force.
     */
    void remove();

    /**
     * The reference frame of the force vector and position.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The reference frame of the force vector and position.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * The force vector. The magnitude of the vector is the strength of the force in Newtons.
     */
    std::tuple<double, double, double> force_vector();

    /**
     * The force vector. The magnitude of the vector is the strength of the force in Newtons.
     */
    void set_force_vector(std::tuple<double, double, double> value);

    /**
     * The part that this force is applied to.
     */
    SpaceCenter::Part part();

    /**
     * The position at which the force acts.
     */
    std::tuple<double, double, double> position();

    /**
     * The position at which the force acts.
     */
    void set_position(std::tuple<double, double, double> value);

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> force_vector_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::tuple<double, double, double>> position_stream();
  };

  /**
   * An air intake. Obtained by calling SpaceCenter::Part::intake.
   */
  class Intake : public krpc::Object<Intake> {
   public:
    explicit Intake(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the intake is open.
     */
    void set_open(bool value);

    /**
     * The area of the intake's opening, in square meters.
     */
    float area();

    /**
     * Speed of the flow into the intake, in m/s.
     */
    float speed();

    /**
     * The rate of flow into the intake, in units of resource per second.
     */
    float flow();

    /**
     * The part object for this intake.
     */
    SpaceCenter::Part part();

    /**
     * Whether the intake is open.
     */
    bool open();

    ::krpc::Stream<float> area_stream();

    ::krpc::Stream<float> speed_stream();

    ::krpc::Stream<float> flow_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> open_stream();
  };

  /**
   * Landing gear with wheels. Obtained by calling SpaceCenter::Part::landing_gear.
   */
  class LandingGear : public krpc::Object<LandingGear> {
   public:
    explicit LandingGear(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the landing gear is deployed.
     *
     * Fixed landing gear are always deployed.
     * Returns an error if you try to deploy fixed landing gear.
     */
    void set_deployed(bool value);

    /**
     * Whether the landing gear is deployable.
     */
    bool deployable();

    /**
     * Gets the current state of the landing gear.
     *
     * Fixed landing gear are always deployed.
     */
    SpaceCenter::LandingGearState state();

    /**
     * The part object for this landing gear.
     */
    SpaceCenter::Part part();

    /**
     * Whether the landing gear is deployed.
     *
     * Fixed landing gear are always deployed.
     * Returns an error if you try to deploy fixed landing gear.
     */
    bool deployed();

    /**
     * Returns whether the gear is touching the ground.
     */
    bool is_grounded();

    ::krpc::Stream<bool> deployable_stream();

    ::krpc::Stream<SpaceCenter::LandingGearState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> deployed_stream();

    ::krpc::Stream<bool> is_grounded_stream();
  };

  /**
   * A landing leg. Obtained by calling SpaceCenter::Part::landing_leg.
   */
  class LandingLeg : public krpc::Object<LandingLeg> {
   public:
    explicit LandingLeg(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the landing leg is deployed.
     *
     * Fixed landing legs are always deployed.
     * Returns an error if you try to deploy fixed landing gear.
     */
    void set_deployed(bool value);

    /**
     * The current state of the landing leg.
     */
    SpaceCenter::LandingLegState state();

    /**
     * The part object for this landing leg.
     */
    SpaceCenter::Part part();

    /**
     * Returns whether the leg is touching the ground.
     */
    bool is_grounded();

    /**
     * Whether the landing leg is deployed.
     *
     * Fixed landing legs are always deployed.
     * Returns an error if you try to deploy fixed landing gear.
     */
    bool deployed();

    ::krpc::Stream<SpaceCenter::LandingLegState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> is_grounded_stream();

    ::krpc::Stream<bool> deployed_stream();
  };

  /**
   * A launch clamp. Obtained by calling SpaceCenter::Part::launch_clamp.
   */
  class LaunchClamp : public krpc::Object<LaunchClamp> {
   public:
    explicit LaunchClamp(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Releases the docking clamp. Has no effect if the clamp has already been released.
     */
    void release();

    /**
     * The part object for this launch clamp.
     */
    SpaceCenter::Part part();

    ::krpc::Stream<SpaceCenter::Part> part_stream();
  };

  /**
   * A light. Obtained by calling SpaceCenter::Part::light.
   */
  class Light : public krpc::Object<Light> {
   public:
    explicit Light(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The current power usage, in units of charge per second.
     */
    float power_usage();

    /**
     * Whether the light is switched on.
     */
    void set_active(bool value);

    /**
     * The color of the light, as an RGB triple.
     */
    std::tuple<float, float, float> color();

    /**
     * The part object for this light.
     */
    SpaceCenter::Part part();

    /**
     * Whether the light is switched on.
     */
    bool active();

    /**
     * The color of the light, as an RGB triple.
     */
    void set_color(std::tuple<float, float, float> value);

    ::krpc::Stream<float> power_usage_stream();

    ::krpc::Stream<std::tuple<float, float, float>> color_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> active_stream();
  };

  /**
   * This can be used to interact with a specific part module. This includes part modules in stock KSP,
   * and those added by mods.
   *
   * In KSP, each part has zero or more
   * <a href="http://wiki.kerbalspaceprogram.com/wiki/CFG_File_Documentation#MODULES">PartModules</a>
   * associated with it. Each one contains some of the functionality of the part.
   * For example, an engine has a "ModuleEngines" part module that contains all the
   * functionality of an engine.
   */
  class Module : public krpc::Object<Module> {
   public:
    explicit Module(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Returns the value of a field.
     * @param name Name of the field.
     */
    std::string get_field(std::string name);

    /**
     * true if the part has an action with the given name.
     * @param name
     */
    bool has_action(std::string name);

    /**
     * true if the module has an event with the given name.
     * @param name
     */
    bool has_event(std::string name);

    /**
     * Returns true if the module has a field with the given name.
     * @param name Name of the field.
     */
    bool has_field(std::string name);

    /**
     * Set the value of a field to its original value.
     * @param name Name of the field.
     */
    void reset_field(std::string name);

    /**
     * Set the value of an action with the given name.
     * @param name
     * @param value
     */
    void set_action(std::string name, bool value);

    /**
     * Set the value of a field to the given floating point number.
     * @param name Name of the field.
     * @param value Value to set.
     */
    void set_field_float(std::string name, float value);

    /**
     * Set the value of a field to the given integer number.
     * @param name Name of the field.
     * @param value Value to set.
     */
    void set_field_int(std::string name, google::protobuf::int32 value);

    /**
     * Set the value of a field to the given string.
     * @param name Name of the field.
     * @param value Value to set.
     */
    void set_field_string(std::string name, std::string value);

    /**
     * Trigger the named event. Equivalent to clicking the button in the right-click menu of the part.
     * @param name
     */
    void trigger_event(std::string name);

    /**
     * The modules field names and their associated values, as a dictionary.
     * These are the values visible in the right-click menu of the part.
     */
    std::map<std::string, std::string> fields();

    /**
     * The part that contains this module.
     */
    SpaceCenter::Part part();

    /**
     * A list of the names of all of the modules events. Events are the clickable buttons
     * visible in the right-click menu of the part.
     */
    std::vector<std::string> events();

    /**
     * A list of all the names of the modules actions. These are the parts actions that can be assigned
     * to action groups in the in-game editor.
     */
    std::vector<std::string> actions();

    /**
     * Name of the PartModule. For example, "ModuleEngines".
     */
    std::string name();

    ::krpc::Stream<std::string> get_field_stream(std::string name);

    ::krpc::Stream<bool> has_action_stream(std::string name);

    ::krpc::Stream<bool> has_event_stream(std::string name);

    ::krpc::Stream<bool> has_field_stream(std::string name);

    ::krpc::Stream<std::map<std::string, std::string>> fields_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::vector<std::string>> events_stream();

    ::krpc::Stream<std::vector<std::string>> actions_stream();

    ::krpc::Stream<std::string> name_stream();
  };

  /**
   * Represents a maneuver node. Can be created using SpaceCenter::Control::add_node.
   */
  class Node : public krpc::Object<Node> {
   public:
    explicit Node(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Returns a vector whose direction the direction of the maneuver node burn, and whose magnitude
     * is the delta-v of the burn in m/s.
     * @param referenceFrame
     *
     * Does not change when executing the maneuver node. See SpaceCenter::Node::remaining_burn_vector.
     */
    std::tuple<double, double, double> burn_vector(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the unit direction vector of the maneuver nodes burn in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the position vector of the maneuver node in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns a vector whose direction the direction of the maneuver node burn, and whose magnitude
     * is the delta-v of the burn in m/s. The direction and magnitude change as the burn is executed.
     * @param referenceFrame
     */
    std::tuple<double, double, double> remaining_burn_vector(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Removes the maneuver node.
     */
    void remove();

    /**
     * Gets the remaining delta-v of the maneuver node, in meters per second. Changes as the node
     * is executed. This is equivalent to the delta-v reported in-game.
     */
    double remaining_delta_v();

    /**
     * Gets the reference frame that is fixed relative to the maneuver node's burn.
     *
     * - The origin is at the position of the maneuver node.
     * - The y-axis points in the direction of the burn.
     * - The x-axis and z-axis point in arbitrary but fixed directions.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The magnitude of the maneuver nodes delta-v in the normal direction, in meters per second.
     */
    void set_normal(double value);

    /**
     * The magnitude of the maneuver nodes delta-v in the normal direction, in meters per second.
     */
    double normal();

    /**
     * The magnitude of the maneuver nodes delta-v in the radial direction, in meters per second.
     */
    void set_radial(double value);

    /**
     * The universal time at which the maneuver will occur, in seconds.
     */
    double ut();

    /**
     * The delta-v of the maneuver node, in meters per second.
     *
     * Does not change when executing the maneuver node. See SpaceCenter::Node::remaining_delta_v.
     */
    double delta_v();

    /**
     * The orbit that results from executing the maneuver node.
     */
    SpaceCenter::Orbit orbit();

    /**
     * The delta-v of the maneuver node, in meters per second.
     *
     * Does not change when executing the maneuver node. See SpaceCenter::Node::remaining_delta_v.
     */
    void set_delta_v(double value);

    /**
     * The magnitude of the maneuver nodes delta-v in the prograde direction, in meters per second.
     */
    void set_prograde(double value);

    /**
     * Gets the reference frame that is fixed relative to the maneuver node, and
     * orientated with the orbital prograde/normal/radial directions of the
     * original orbit at the maneuver node's position.
     *
     * - The origin is at the position of the maneuver node.
     * - The x-axis points in the orbital anti-radial direction of the original
     *   orbit, at the position of the maneuver node.
     * - The y-axis points in the orbital prograde direction of the original
     *   orbit, at the position of the maneuver node.
     * - The z-axis points in the orbital normal direction of the original orbit,
     *   at the position of the maneuver node.
     */
    SpaceCenter::ReferenceFrame orbital_reference_frame();

    /**
     * The universal time at which the maneuver will occur, in seconds.
     */
    void set_ut(double value);

    /**
     * The magnitude of the maneuver nodes delta-v in the radial direction, in meters per second.
     */
    double radial();

    /**
     * The magnitude of the maneuver nodes delta-v in the prograde direction, in meters per second.
     */
    double prograde();

    /**
     * The time until the maneuver node will be encountered, in seconds.
     */
    double time_to();

    ::krpc::Stream<std::tuple<double, double, double>> burn_vector_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> remaining_burn_vector_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<double> remaining_delta_v_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<double> normal_stream();

    ::krpc::Stream<double> ut_stream();

    ::krpc::Stream<double> delta_v_stream();

    ::krpc::Stream<SpaceCenter::Orbit> orbit_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> orbital_reference_frame_stream();

    ::krpc::Stream<double> radial_stream();

    ::krpc::Stream<double> prograde_stream();

    ::krpc::Stream<double> time_to_stream();
  };

  /**
   * Describes an orbit. For example, the orbit of a vessel, obtained by calling
   * SpaceCenter::Vessel::orbit, or a celestial body, obtained by calling
   * SpaceCenter::CelestialBody::orbit.
   */
  class Orbit : public krpc::Object<Orbit> {
   public:
    explicit Orbit(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The eccentric anomaly at the given universal time.
     * @param ut The universal time, in seconds.
     */
    double eccentric_anomaly_at_ut(double ut);

    /**
     * The orbital speed at the given time, in meters per second.
     * @param time Time from now, in seconds.
     */
    double orbital_speed_at(double time);

    /**
     * The orbital radius at the point in the orbit given by the true anomaly.
     * @param trueAnomaly The true anomaly.
     */
    double radius_at_true_anomaly(double true_anomaly);

    /**
     * The true anomaly at the given orbital radius.
     * @param radius The orbital radius in meters.
     */
    double true_anomaly_at_radius(double radius);

    /**
     * The true anomaly at the given time.
     * @param ut The universal time in seconds.
     */
    double true_anomaly_at_ut(double ut);

    /**
     * The universal time, in seconds, corresponding to the given true anomaly.
     * @param trueAnomaly True anomaly.
     */
    double ut_at_true_anomaly(double true_anomaly);

    /**
     * The unit direction vector from which the orbits longitude of ascending node is measured,
     * in the given reference frame.
     * @param referenceFrame
     */
    static std::tuple<double, double, double> reference_plane_direction(Client& client, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The unit direction vector that is normal to the orbits reference plane, in the given
     * reference frame. The reference plane is the plane from which the orbits inclination is measured.
     * @param referenceFrame
     */
    static std::tuple<double, double, double> reference_plane_normal(Client& client, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The orbital period, in seconds.
     */
    double period();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Eccentric_anomaly">eccentric anomaly</a>.
     */
    double eccentric_anomaly();

    /**
     * The time until the object changes sphere of influence, in seconds. Returns NaN if the
     * object is not going to change sphere of influence.
     */
    double time_to_soi_change();

    /**
     * The apoapsis of the orbit, in meters, above the sea level of the body being orbited.
     *
     * This is equal to SpaceCenter::Orbit::apoapsis minus the equatorial radius of the body.
     */
    double apoapsis_altitude();

    /**
     * The current orbital speed of the object in meters per second.
     *
     * This value will change over time if the orbit is elliptical.
     */
    double speed();

    /**
     * The current orbital speed in meters per second.
     */
    double orbital_speed();

    /**
     * The time until the object reaches apoapsis, in seconds.
     */
    double time_to_apoapsis();

    /**
     * If the object is going to change sphere of influence in the future, returns the new orbit
     * after the change. Otherwise returns null.
     */
    SpaceCenter::Orbit next_orbit();

    /**
     * The periapsis of the orbit, in meters, above the sea level of the body being orbited.
     *
     * This is equal to SpaceCenter::Orbit::periapsis minus the equatorial radius of the body.
     */
    double periapsis_altitude();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Mean_anomaly">mean anomaly at epoch</a>.
     */
    double mean_anomaly_at_epoch();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Mean_anomaly">mean anomaly</a>.
     */
    double mean_anomaly();

    /**
     * The time since the epoch (the point at which the
     * <a href="https://en.wikipedia.org/wiki/Mean_anomaly">mean anomaly at epoch</a> was measured, in seconds.
     */
    double epoch();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Argument_of_periapsis">argument of periapsis</a>, in radians.
     */
    double argument_of_periapsis();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Orbital_inclination">inclination</a> of the orbit,
     * in radians.
     */
    double inclination();

    /**
     * The celestial body (e.g. planet or moon) around which the object is orbiting.
     */
    SpaceCenter::CelestialBody body();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Orbital_eccentricity">eccentricity</a> of the orbit.
     */
    double eccentricity();

    /**
     * The periapsis of the orbit, in meters, from the center of mass of the body being orbited.
     *
     * For the periapsis altitude reported on the in-game map view, use SpaceCenter::Orbit::periapsis_altitude.
     */
    double periapsis();

    /**
     * The semi-major axis of the orbit, in meters.
     */
    double semi_major_axis();

    /**
     * The time until the object reaches periapsis, in seconds.
     */
    double time_to_periapsis();

    /**
     * The <a href="https://en.wikipedia.org/wiki/Longitude_of_the_ascending_node">longitude of the
     * ascending node</a>, in radians.
     */
    double longitude_of_ascending_node();

    /**
     * The semi-minor axis of the orbit, in meters.
     */
    double semi_minor_axis();

    /**
     * Gets the apoapsis of the orbit, in meters, from the center of mass of the body being orbited.
     *
     * For the apoapsis altitude reported on the in-game map view, use SpaceCenter::Orbit::apoapsis_altitude.
     */
    double apoapsis();

    /**
     * The current radius of the orbit, in meters. This is the distance between the center
     * of mass of the object in orbit, and the center of mass of the body around which it is orbiting.
     *
     * This value will change over time if the orbit is elliptical.
     */
    double radius();

    /**
     * The <a href="https://en.wikipedia.org/wiki/True_anomaly">true anomaly</a>.
     */
    double true_anomaly();

    ::krpc::Stream<double> eccentric_anomaly_at_ut_stream(double ut);

    ::krpc::Stream<double> orbital_speed_at_stream(double time);

    ::krpc::Stream<double> radius_at_true_anomaly_stream(double true_anomaly);

    ::krpc::Stream<double> true_anomaly_at_radius_stream(double radius);

    ::krpc::Stream<double> true_anomaly_at_ut_stream(double ut);

    ::krpc::Stream<double> ut_at_true_anomaly_stream(double true_anomaly);

    static ::krpc::Stream<std::tuple<double, double, double>> reference_plane_direction_stream(Client& client, SpaceCenter::ReferenceFrame reference_frame);

    static ::krpc::Stream<std::tuple<double, double, double>> reference_plane_normal_stream(Client& client, SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<double> period_stream();

    ::krpc::Stream<double> eccentric_anomaly_stream();

    ::krpc::Stream<double> time_to_soi_change_stream();

    ::krpc::Stream<double> apoapsis_altitude_stream();

    ::krpc::Stream<double> speed_stream();

    ::krpc::Stream<double> orbital_speed_stream();

    ::krpc::Stream<double> time_to_apoapsis_stream();

    ::krpc::Stream<SpaceCenter::Orbit> next_orbit_stream();

    ::krpc::Stream<double> periapsis_altitude_stream();

    ::krpc::Stream<double> mean_anomaly_at_epoch_stream();

    ::krpc::Stream<double> mean_anomaly_stream();

    ::krpc::Stream<double> epoch_stream();

    ::krpc::Stream<double> argument_of_periapsis_stream();

    ::krpc::Stream<double> inclination_stream();

    ::krpc::Stream<SpaceCenter::CelestialBody> body_stream();

    ::krpc::Stream<double> eccentricity_stream();

    ::krpc::Stream<double> periapsis_stream();

    ::krpc::Stream<double> semi_major_axis_stream();

    ::krpc::Stream<double> time_to_periapsis_stream();

    ::krpc::Stream<double> longitude_of_ascending_node_stream();

    ::krpc::Stream<double> semi_minor_axis_stream();

    ::krpc::Stream<double> apoapsis_stream();

    ::krpc::Stream<double> radius_stream();

    ::krpc::Stream<double> true_anomaly_stream();
  };

  /**
   * A parachute. Obtained by calling SpaceCenter::Part::parachute.
   */
  class Parachute : public krpc::Object<Parachute> {
   public:
    explicit Parachute(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Deploys the parachute. This has no effect if the parachute has already
     * been deployed.
     */
    void deploy();

    /**
     * The minimum pressure at which the parachute will semi-deploy, in atmospheres.
     */
    float deploy_min_pressure();

    /**
     * The altitude at which the parachute will full deploy, in meters.
     */
    void set_deploy_altitude(float value);

    /**
     * The altitude at which the parachute will full deploy, in meters.
     */
    float deploy_altitude();

    /**
     * The current state of the parachute.
     */
    SpaceCenter::ParachuteState state();

    /**
     * The part object for this parachute.
     */
    SpaceCenter::Part part();

    /**
     * The minimum pressure at which the parachute will semi-deploy, in atmospheres.
     */
    void set_deploy_min_pressure(float value);

    /**
     * Whether the parachute has been deployed.
     */
    bool deployed();

    ::krpc::Stream<float> deploy_min_pressure_stream();

    ::krpc::Stream<float> deploy_altitude_stream();

    ::krpc::Stream<SpaceCenter::ParachuteState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> deployed_stream();
  };

  /**
   * Represents an individual part. Vessels are made up of multiple parts.
   * Instances of this class can be obtained by several methods in SpaceCenter::Parts.
   */
  class Part : public krpc::Object<Part> {
   public:
    explicit Part(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Exert a constant force on the part, acting at the given position.
     * Returns an object that can be used to remove or modify the force.
     */
    SpaceCenter::Force add_force(std::tuple<double, double, double> force, std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The axis-aligned bounding box of the vessel in the given reference frame.
     * Returns the minimum and maximum vertices of the box.
     * @param referenceFrame
     *
     * This is computed from the collision meshes of the part.
     * If the part is not collidable, the box has zero volume and is centered on
     * the SpaceCenter::Part::position of the part.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > bounding_box(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The position of the parts center of mass in the given reference frame.
     * If the part is physicsless, this is equivalent to SpaceCenter::Part::position.
     * @param referenceFrame
     */
    std::tuple<double, double, double> center_of_mass(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The direction of the part in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Exert an instantaneous force on the part, acting at the given position.
     *
     * The force is applied instantaneously in a single physics update.
     */
    void instantaneous_force(std::tuple<double, double, double> force, std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The position of the part in the given reference frame.
     *
     * This is a fixed position in the part, defined by the parts model.
     * It s not necessarily the same as the parts center of mass.
     * Use SpaceCenter::Part::center_of_mass to get the parts center of mass.
     * @param referenceFrame
     */
    std::tuple<double, double, double> position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The rotation of the part in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double, double> rotation(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The velocity of the part in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> velocity(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * An SpaceCenter::Engine if the part is an engine, otherwise null.
     */
    SpaceCenter::Engine engine();

    /**
     * Whether the part is highlighted.
     */
    void set_highlighted(bool value);

    /**
     * Temperature of the part, in Kelvin.
     */
    double temperature();

    /**
     * The parts that are connected to this part via fuel lines, where the direction of the fuel line is into this part.
     */
    std::vector<SpaceCenter::Part> fuel_lines_from();

    /**
     * A SpaceCenter::Fairing if the part is a fairing, otherwise null.
     */
    SpaceCenter::Fairing fairing();

    /**
     * Maximum temperature that the part can survive, in Kelvin.
     */
    double max_temperature();

    /**
     * A measure of how much energy it takes to increase the skin temperature of the part, in Joules per Kelvin.
     */
    float thermal_skin_mass();

    /**
     * The name tag for the part. Can be set to a custom string using the in-game user interface.
     *
     * This requires either the <a href="http://github.com/krpc/NameTag/releases/latest">NameTag</a> or
     * <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/61827-/">kOS</a> mods to be installed.
     */
    std::string tag();

    /**
     * The rate at which heat energy is conducting into or out of the part via contact with other parts.
     * Measured in energy per unit time, or power, in Watts.
     * A positive value means the part is gaining heat energy, and negative means it is losing heat energy.
     */
    float thermal_conduction_flux();

    /**
     * A SpaceCenter::ReactionWheel if the part is a reaction wheel, otherwise null.
     */
    SpaceCenter::ReactionWheel reaction_wheel();

    /**
     * A SpaceCenter::Parachute if the part is a parachute, otherwise null.
     */
    SpaceCenter::Parachute parachute();

    /**
     * The vessel that contains this part.
     */
    SpaceCenter::Vessel vessel();

    /**
     * The cost of the part, in units of funds.
     */
    double cost();

    /**
     * The parts parent. Returns null if the part does not have a parent.
     * This, in combination with SpaceCenter::Part::children, can be used to traverse the vessels parts tree.
     */
    SpaceCenter::Part parent();

    /**
     * A SpaceCenter::LaunchClamp if the part is a launch clamp, otherwise null.
     */
    SpaceCenter::LaunchClamp launch_clamp();

    /**
     * The rate at which heat energy is convecting into or out of the part from the surrounding atmosphere.
     * Measured in energy per unit time, or power, in Watts.
     * A positive value means the part is gaining heat energy, and negative means it is losing heat energy.
     */
    float thermal_convection_flux();

    /**
     * A SpaceCenter::ResourceConverter if the part is a resource converter, otherwise null.
     */
    SpaceCenter::ResourceConverter resource_converter();

    /**
     * A SpaceCenter::LandingGear if the part is a landing gear, otherwise null.
     */
    SpaceCenter::LandingGear landing_gear();

    /**
     * A measure of how much energy it takes to increase the internal temperature of the part, in Joules per Kelvin.
     */
    float thermal_mass();

    /**
     * The parts children. Returns an empty list if the part has no children.
     * This, in combination with SpaceCenter::Part::parent, can be used to traverse the vessels parts tree.
     */
    std::vector<SpaceCenter::Part> children();

    /**
     * A SpaceCenter::Radiator if the part is a radiator, otherwise null.
     */
    SpaceCenter::Radiator radiator();

    /**
     * The inertia tensor of the part in the parts reference frame (SpaceCenter::ReferenceFrame).
     * Returns the 3x3 matrix as a list of elements, in row-major order.
     */
    std::vector<double> inertia_tensor();

    /**
     * A measure of how much energy it takes to increase the temperature of the resources contained in the part, in Joules per Kelvin.
     */
    float thermal_resource_mass();

    /**
     * A SpaceCenter::LandingLeg if the part is a landing leg, otherwise null.
     */
    SpaceCenter::LandingLeg landing_leg();

    /**
     * Whether this part is crossfeed capable.
     */
    bool crossfeed();

    /**
     * Title of the part, as shown when the part is right clicked in-game. For example "Mk1-2 Command Pod".
     */
    std::string title();

    /**
     * A SpaceCenter::RCS if the part is an RCS block/thruster, otherwise null.
     */
    SpaceCenter::RCS rcs();

    /**
     * Whether the part is highlighted.
     */
    bool highlighted();

    /**
     * The impact tolerance of the part, in meters per second.
     */
    double impact_tolerance();

    /**
     * An SpaceCenter::Experiment if the part is a science experiment, otherwise null.
     */
    SpaceCenter::Experiment experiment();

    /**
     * The reference frame that is fixed relative to this part, and centered on its center of mass.
     *
     * - The origin is at the center of mass of the part, as returned by SpaceCenter::Part::center_of_mass.
     * - The axes rotate with the part.
     * - The x, y and z axis directions depend on the design of the part.
     *
     * For docking port parts, this reference frame is not necessarily equivalent to the reference frame
     * for the docking port, returned by SpaceCenter::DockingPort::reference_frame.
     */
    SpaceCenter::ReferenceFrame center_of_mass_reference_frame();

    /**
     * The stage in which this part will be decoupled. Returns -1 if the part is never decoupled from the vessel.
     */
    google::protobuf::int32 decouple_stage();

    /**
     * Whether the part is <a href="http://wiki.kerbalspaceprogram.com/wiki/Massless_part">massless</a>.
     */
    bool massless();

    /**
     * A SpaceCenter::Sensor if the part is a sensor, otherwise null.
     */
    SpaceCenter::Sensor sensor();

    /**
     * A SpaceCenter::Resources object for the part.
     */
    SpaceCenter::Resources resources();

    /**
     * A SpaceCenter::CargoBay if the part is a cargo bay, otherwise null.
     */
    SpaceCenter::CargoBay cargo_bay();

    /**
     * The reference frame that is fixed relative to this part, and centered on a fixed position within the part, defined by the parts model.
     *
     * - The origin is at the position of the part, as returned by SpaceCenter::Part::position.
     * - The axes rotate with the part.
     * - The x, y and z axis directions depend on the design of the part.
     *
     * For docking port parts, this reference frame is not necessarily equivalent to the reference frame
     * for the docking port, returned by SpaceCenter::DockingPort::reference_frame.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The moment of inertia of the part in kg.m^2 around its center of mass
     * in the parts reference frame (SpaceCenter::ReferenceFrame).
     */
    std::tuple<double, double, double> moment_of_inertia();

    /**
     * Temperature of the skin of the part, in Kelvin.
     */
    double skin_temperature();

    /**
     * Whether the part is radially attached to its parent, i.e. on the side of its parent.
     * If the part has no parent, returns false.
     */
    bool radially_attached();

    /**
     * A SpaceCenter::ResourceHarvester if the part is a resource harvester, otherwise null.
     */
    SpaceCenter::ResourceHarvester resource_harvester();

    /**
     * The rate at which heat energy is radiating into or out of the part from the surrounding environment.
     * Measured in energy per unit time, or power, in Watts.
     * A positive value means the part is gaining heat energy, and negative means it is losing heat energy.
     */
    float thermal_radiation_flux();

    /**
     * Whether this part is a fuel line.
     */
    bool is_fuel_line();

    /**
     * The rate at which heat energy is transferring between the part's skin and its internals.
     * Measured in energy per unit time, or power, in Watts.
     * A positive value means the part's internals are gaining heat energy,
     * and negative means its skin is gaining heat energy.
     */
    float thermal_skin_to_internal_flux();

    /**
     * The color used to highlight the part.
     */
    void set_highlight_color(std::tuple<double, double, double> value);

    /**
     * The stage in which this part will be activated. Returns -1 if the part is not activated by staging.
     */
    google::protobuf::int32 stage();

    /**
     * The parts that are connected to this part via fuel lines, where the direction of the fuel line is out of this part.
     */
    std::vector<SpaceCenter::Part> fuel_lines_to();

    /**
     * An SpaceCenter::Intake if the part is an intake, otherwise null.
     *
     * This includes any part that generates thrust. This covers many different types of engine,
     * including liquid fuel rockets, solid rocket boosters and jet engines.
     * For RCS thrusters see SpaceCenter::RCS.
     */
    SpaceCenter::Intake intake();

    /**
     * Internal name of the part, as used in
     * <a href="http://wiki.kerbalspaceprogram.com/wiki/CFG_File_Documentation">part cfg files</a>.
     * For example "Mark1-2Pod".
     */
    std::string name();

    /**
     * The dynamic pressure acting on the part, in Pascals.
     */
    float dynamic_pressure();

    /**
     * A SpaceCenter::Decoupler if the part is a decoupler, otherwise null.
     */
    SpaceCenter::Decoupler decoupler();

    /**
     * A SpaceCenter::Light if the part is a light, otherwise null.
     */
    SpaceCenter::Light light();

    /**
     * The rate at which heat energy is begin generated by the part.
     * For example, some engines generate heat by combusting fuel.
     * Measured in energy per unit time, or power, in Watts.
     * A positive value means the part is gaining heat energy, and negative means it is losing heat energy.
     */
    float thermal_internal_flux();

    /**
     * The modules for this part.
     */
    std::vector<SpaceCenter::Module> modules();

    /**
     * Whether the part is axially attached to its parent, i.e. on the top
     * or bottom of its parent. If the part has no parent, returns false.
     */
    bool axially_attached();

    /**
     * The name tag for the part. Can be set to a custom string using the in-game user interface.
     *
     * This requires either the <a href="http://github.com/krpc/NameTag/releases/latest">NameTag</a> or
     * <a href="http://forum.kerbalspaceprogram.com/index.php?/topic/61827-/">kOS</a> mods to be installed.
     */
    void set_tag(std::string value);

    /**
     * The color used to highlight the part.
     */
    std::tuple<double, double, double> highlight_color();

    /**
     * A SpaceCenter::ControlSurface if the part is an aerodynamic control surface, otherwise null.
     */
    SpaceCenter::ControlSurface control_surface();

    /**
     * Whether the part is shielded from the exterior of the vessel, for example by a fairing.
     */
    bool shielded();

    /**
     * A SpaceCenter::DockingPort if the part is a docking port, otherwise null.
     */
    SpaceCenter::DockingPort docking_port();

    /**
     * The current mass of the part, including resources it contains, in kilograms.
     * Returns zero if the part is massless.
     */
    double mass();

    /**
     * Maximum temperature that the skin of the part can survive, in Kelvin.
     */
    double max_skin_temperature();

    /**
     * A SpaceCenter::SolarPanel if the part is a solar panel, otherwise null.
     */
    SpaceCenter::SolarPanel solar_panel();

    /**
     * The mass of the part, not including any resources it contains, in kilograms. Returns zero if the part is massless.
     */
    double dry_mass();

    ::krpc::Stream<SpaceCenter::Force> add_force_stream(std::tuple<double, double, double> force, std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> bounding_box_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> center_of_mass_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> velocity_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::Engine> engine_stream();

    ::krpc::Stream<double> temperature_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Part>> fuel_lines_from_stream();

    ::krpc::Stream<SpaceCenter::Fairing> fairing_stream();

    ::krpc::Stream<double> max_temperature_stream();

    ::krpc::Stream<float> thermal_skin_mass_stream();

    ::krpc::Stream<std::string> tag_stream();

    ::krpc::Stream<float> thermal_conduction_flux_stream();

    ::krpc::Stream<SpaceCenter::ReactionWheel> reaction_wheel_stream();

    ::krpc::Stream<SpaceCenter::Parachute> parachute_stream();

    ::krpc::Stream<SpaceCenter::Vessel> vessel_stream();

    ::krpc::Stream<double> cost_stream();

    ::krpc::Stream<SpaceCenter::Part> parent_stream();

    ::krpc::Stream<SpaceCenter::LaunchClamp> launch_clamp_stream();

    ::krpc::Stream<float> thermal_convection_flux_stream();

    ::krpc::Stream<SpaceCenter::ResourceConverter> resource_converter_stream();

    ::krpc::Stream<SpaceCenter::LandingGear> landing_gear_stream();

    ::krpc::Stream<float> thermal_mass_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Part>> children_stream();

    ::krpc::Stream<SpaceCenter::Radiator> radiator_stream();

    ::krpc::Stream<std::vector<double>> inertia_tensor_stream();

    ::krpc::Stream<float> thermal_resource_mass_stream();

    ::krpc::Stream<SpaceCenter::LandingLeg> landing_leg_stream();

    ::krpc::Stream<bool> crossfeed_stream();

    ::krpc::Stream<std::string> title_stream();

    ::krpc::Stream<SpaceCenter::RCS> rcs_stream();

    ::krpc::Stream<bool> highlighted_stream();

    ::krpc::Stream<double> impact_tolerance_stream();

    ::krpc::Stream<SpaceCenter::Experiment> experiment_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> center_of_mass_reference_frame_stream();

    ::krpc::Stream<google::protobuf::int32> decouple_stage_stream();

    ::krpc::Stream<bool> massless_stream();

    ::krpc::Stream<SpaceCenter::Sensor> sensor_stream();

    ::krpc::Stream<SpaceCenter::Resources> resources_stream();

    ::krpc::Stream<SpaceCenter::CargoBay> cargo_bay_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> moment_of_inertia_stream();

    ::krpc::Stream<double> skin_temperature_stream();

    ::krpc::Stream<bool> radially_attached_stream();

    ::krpc::Stream<SpaceCenter::ResourceHarvester> resource_harvester_stream();

    ::krpc::Stream<float> thermal_radiation_flux_stream();

    ::krpc::Stream<bool> is_fuel_line_stream();

    ::krpc::Stream<float> thermal_skin_to_internal_flux_stream();

    ::krpc::Stream<google::protobuf::int32> stage_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Part>> fuel_lines_to_stream();

    ::krpc::Stream<SpaceCenter::Intake> intake_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<float> dynamic_pressure_stream();

    ::krpc::Stream<SpaceCenter::Decoupler> decoupler_stream();

    ::krpc::Stream<SpaceCenter::Light> light_stream();

    ::krpc::Stream<float> thermal_internal_flux_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Module>> modules_stream();

    ::krpc::Stream<bool> axially_attached_stream();

    ::krpc::Stream<std::tuple<double, double, double>> highlight_color_stream();

    ::krpc::Stream<SpaceCenter::ControlSurface> control_surface_stream();

    ::krpc::Stream<bool> shielded_stream();

    ::krpc::Stream<SpaceCenter::DockingPort> docking_port_stream();

    ::krpc::Stream<double> mass_stream();

    ::krpc::Stream<double> max_skin_temperature_stream();

    ::krpc::Stream<SpaceCenter::SolarPanel> solar_panel_stream();

    ::krpc::Stream<double> dry_mass_stream();
  };

  /**
   * Instances of this class are used to interact with the parts of a vessel.
   * An instance can be obtained by calling SpaceCenter::Vessel::parts.
   */
  class Parts : public krpc::Object<Parts> {
   public:
    explicit Parts(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * A list of all parts that are decoupled in the given stage.
     * @param stage
     */
    std::vector<SpaceCenter::Part> in_decouple_stage(google::protobuf::int32 stage);

    /**
     * A list of all parts that are activated in the given stage.
     * @param stage
     */
    std::vector<SpaceCenter::Part> in_stage(google::protobuf::int32 stage);

    /**
     * A list of modules (combined across all parts in the vessel) whose
     * SpaceCenter::Module::name is moduleName.
     * @param moduleName
     */
    std::vector<SpaceCenter::Module> modules_with_name(std::string module_name);

    /**
     * A list of all parts that contain a SpaceCenter::Module whose
     * SpaceCenter::Module::name is moduleName.
     * @param moduleName
     */
    std::vector<SpaceCenter::Part> with_module(std::string module_name);

    /**
     * A list of parts whose SpaceCenter::Part::name is name.
     * @param name
     */
    std::vector<SpaceCenter::Part> with_name(std::string name);

    /**
     * A list of all parts whose SpaceCenter::Part::tag is tag.
     * @param tag
     */
    std::vector<SpaceCenter::Part> with_tag(std::string tag);

    /**
     * A list of all parts whose SpaceCenter::Part::title is title.
     * @param title
     */
    std::vector<SpaceCenter::Part> with_title(std::string title);

    /**
     * A list of all of the vessels parts.
     */
    std::vector<SpaceCenter::Part> all();

    /**
     * A list of all landing legs attached to the vessel.
     */
    std::vector<SpaceCenter::LandingLeg> landing_legs();

    /**
     * A list of all radiators in the vessel.
     */
    std::vector<SpaceCenter::Radiator> radiators();

    /**
     * A list of all science experiments in the vessel.
     */
    std::vector<SpaceCenter::Experiment> experiments();

    /**
     * A list of all landing gear attached to the vessel.
     */
    std::vector<SpaceCenter::LandingGear> landing_gear();

    /**
     * A list of all decouplers in the vessel.
     */
    std::vector<SpaceCenter::Decoupler> decouplers();

    /**
     * A list of all solar panels in the vessel.
     */
    std::vector<SpaceCenter::SolarPanel> solar_panels();

    /**
     * A list of all resource converters in the vessel.
     */
    std::vector<SpaceCenter::ResourceConverter> resource_converters();

    /**
     * A list of all engines in the vessel.
     *
     * This includes any part that generates thrust. This covers many different types of engine,
     * including liquid fuel rockets, solid rocket boosters, jet engines and RCS thrusters.
     */
    std::vector<SpaceCenter::Engine> engines();

    /**
     * A list of all RCS blocks/thrusters in the vessel.
     */
    std::vector<SpaceCenter::RCS> rcs();

    /**
     * A list of all lights in the vessel.
     */
    std::vector<SpaceCenter::Light> lights();

    /**
     * A list of all reaction wheels in the vessel.
     */
    std::vector<SpaceCenter::ReactionWheel> reaction_wheels();

    /**
     * The part from which the vessel is controlled.
     */
    void set_controlling(SpaceCenter::Part value);

    /**
     * A list of all fairings in the vessel.
     */
    std::vector<SpaceCenter::Fairing> fairings();

    /**
     * The part from which the vessel is controlled.
     */
    SpaceCenter::Part controlling();

    /**
     * A list of all intakes in the vessel.
     */
    std::vector<SpaceCenter::Intake> intakes();

    /**
     * A list of all sensors in the vessel.
     */
    std::vector<SpaceCenter::Sensor> sensors();

    /**
     * A list of all control surfaces in the vessel.
     */
    std::vector<SpaceCenter::ControlSurface> control_surfaces();

    /**
     * A list of all cargo bays in the vessel.
     */
    std::vector<SpaceCenter::CargoBay> cargo_bays();

    /**
     * A list of all docking ports in the vessel.
     */
    std::vector<SpaceCenter::DockingPort> docking_ports();

    /**
     * A list of all resource harvesters in the vessel.
     */
    std::vector<SpaceCenter::ResourceHarvester> resource_harvesters();

    /**
     * A list of all parachutes in the vessel.
     */
    std::vector<SpaceCenter::Parachute> parachutes();

    /**
     * A list of all launch clamps attached to the vessel.
     */
    std::vector<SpaceCenter::LaunchClamp> launch_clamps();

    /**
     * The vessels root part.
     */
    SpaceCenter::Part root();

    ::krpc::Stream<std::vector<SpaceCenter::Part>> in_decouple_stage_stream(google::protobuf::int32 stage);

    ::krpc::Stream<std::vector<SpaceCenter::Part>> in_stage_stream(google::protobuf::int32 stage);

    ::krpc::Stream<std::vector<SpaceCenter::Module>> modules_with_name_stream(std::string module_name);

    ::krpc::Stream<std::vector<SpaceCenter::Part>> with_module_stream(std::string module_name);

    ::krpc::Stream<std::vector<SpaceCenter::Part>> with_name_stream(std::string name);

    ::krpc::Stream<std::vector<SpaceCenter::Part>> with_tag_stream(std::string tag);

    ::krpc::Stream<std::vector<SpaceCenter::Part>> with_title_stream(std::string title);

    ::krpc::Stream<std::vector<SpaceCenter::Part>> all_stream();

    ::krpc::Stream<std::vector<SpaceCenter::LandingLeg>> landing_legs_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Radiator>> radiators_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Experiment>> experiments_stream();

    ::krpc::Stream<std::vector<SpaceCenter::LandingGear>> landing_gear_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Decoupler>> decouplers_stream();

    ::krpc::Stream<std::vector<SpaceCenter::SolarPanel>> solar_panels_stream();

    ::krpc::Stream<std::vector<SpaceCenter::ResourceConverter>> resource_converters_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Engine>> engines_stream();

    ::krpc::Stream<std::vector<SpaceCenter::RCS>> rcs_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Light>> lights_stream();

    ::krpc::Stream<std::vector<SpaceCenter::ReactionWheel>> reaction_wheels_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Fairing>> fairings_stream();

    ::krpc::Stream<SpaceCenter::Part> controlling_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Intake>> intakes_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Sensor>> sensors_stream();

    ::krpc::Stream<std::vector<SpaceCenter::ControlSurface>> control_surfaces_stream();

    ::krpc::Stream<std::vector<SpaceCenter::CargoBay>> cargo_bays_stream();

    ::krpc::Stream<std::vector<SpaceCenter::DockingPort>> docking_ports_stream();

    ::krpc::Stream<std::vector<SpaceCenter::ResourceHarvester>> resource_harvesters_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Parachute>> parachutes_stream();

    ::krpc::Stream<std::vector<SpaceCenter::LaunchClamp>> launch_clamps_stream();

    ::krpc::Stream<SpaceCenter::Part> root_stream();
  };

  /**
   * A propellant for an engine. Obtains by calling SpaceCenter::Engine::propellants.
   */
  class Propellant : public krpc::Object<Propellant> {
   public:
    explicit Propellant(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The propellant ratio.
     */
    float ratio();

    /**
     * If this propellant is deprived.
     */
    bool is_deprived();

    /**
     * The current amount of propellant.
     */
    double current_amount();

    /**
     * If this propellant has a stack gauge or not.
     */
    bool draw_stack_gauge();

    /**
     * If this propellant should be ignored for thrust curve calculations.
     */
    bool ignore_for_thrust_curve();

    /**
     * The total amount of the underlying resource currently reachable given resource flow rules.
     */
    double total_resource_available();

    /**
     * The total vehicle capacity for the underlying propellant resource, restricted by resource flow rules.
     */
    double total_resource_capacity();

    /**
     * If this propellant should be ignored when calculating required mass flow given specific impulse.
     */
    bool ignore_for_isp();

    /**
     * The required amount of propellant.
     */
    double current_requirement();

    /**
     * The name of the propellant.
     */
    std::string name();

    ::krpc::Stream<float> ratio_stream();

    ::krpc::Stream<bool> is_deprived_stream();

    ::krpc::Stream<double> current_amount_stream();

    ::krpc::Stream<bool> draw_stack_gauge_stream();

    ::krpc::Stream<bool> ignore_for_thrust_curve_stream();

    ::krpc::Stream<double> total_resource_available_stream();

    ::krpc::Stream<double> total_resource_capacity_stream();

    ::krpc::Stream<bool> ignore_for_isp_stream();

    ::krpc::Stream<double> current_requirement_stream();

    ::krpc::Stream<std::string> name_stream();
  };

  /**
   * An RCS block or thruster. Obtained by calling SpaceCenter::Part::rcs.
   */
  class RCS : public krpc::Object<RCS> {
   public:
    explicit RCS(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the RCS thruster will fire when roll control input is given.
     */
    void set_roll_enabled(bool value);

    /**
     * The vacuum specific impulse of the RCS, in seconds.
     */
    float vacuum_specific_impulse();

    /**
     * Whether the RCS thruster will fire when roll control input is given.
     */
    void set_right_enabled(bool value);

    /**
     * Whether the RCS has fuel available.
     *
     * The RCS thruster must be activated for this property to update correctly.
     */
    bool has_fuel();

    /**
     * The current specific impulse of the RCS, in seconds. Returns zero
     * if the RCS is not active.
     */
    float specific_impulse();

    /**
     * Whether the RCS thruster will fire when roll control input is given.
     */
    bool roll_enabled();

    /**
     * Whether the RCS thruster will fire when yaw control input is given.
     */
    bool yaw_enabled();

    /**
     * Whether the RCS thrusters are enabled.
     */
    void set_enabled(bool value);

    /**
     * Whether the RCS thruster will fire when yaw control input is given.
     */
    void set_up_enabled(bool value);

    /**
     * The maximum amount of thrust that can be produced by the RCS thrusters when active in a vacuum, in Newtons.
     */
    float max_vacuum_thrust();

    /**
     * Whether the RCS thruster will fire when roll control input is given.
     */
    bool right_enabled();

    /**
     * Whether the RCS thruster will fire when yaw control input is given.
     */
    bool up_enabled();

    /**
     * The part object for this RCS.
     */
    SpaceCenter::Part part();

    /**
     * A list of thrusters, one of each nozzel in the RCS part.
     */
    std::vector<SpaceCenter::Thruster> thrusters();

    /**
     * Whether the RCS thrusters are active.
     * An RCS thruster is inactive if the RCS action group is disabled (SpaceCenter::Control::rcs),
     * the RCS thruster itself is not enabled (SpaceCenter::RCS::enabled) or
     * it is covered by a fairing (SpaceCenter::Part::shielded).
     */
    bool active();

    /**
     * The names of resources that the RCS consumes.
     */
    std::vector<std::string> propellants();

    /**
     * The available torque in the pitch, roll and yaw axes of the vessel, in Newton meters.
     * These axes correspond to the coordinate axes of the SpaceCenter::Vessel::reference_frame.
     * Returns zero if the RCS is inactive.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_torque();

    /**
     * The ratios of resources that the RCS consumes. A dictionary mapping resource names
     * to the ratios at which they are consumed by the RCS.
     */
    std::map<std::string, float> propellant_ratios();

    /**
     * The specific impulse of the RCS at sea level on Kerbin, in seconds.
     */
    float kerbin_sea_level_specific_impulse();

    /**
     * Whether the RCS thrusters are enabled.
     */
    bool enabled();

    /**
     * Whether the RCS thruster will fire when yaw control input is given.
     */
    void set_yaw_enabled(bool value);

    /**
     * Whether the RCS thruster will fire when pitch control input is given.
     */
    void set_pitch_enabled(bool value);

    /**
     * Whether the RCS thruster will fire when pitch control input is given.
     */
    void set_forward_enabled(bool value);

    /**
     * The maximum amount of thrust that can be produced by the RCS thrusters when active, in Newtons.
     */
    float max_thrust();

    /**
     * Whether the RCS thruster will fire when pitch control input is given.
     */
    bool pitch_enabled();

    /**
     * Whether the RCS thruster will fire when pitch control input is given.
     */
    bool forward_enabled();

    ::krpc::Stream<float> vacuum_specific_impulse_stream();

    ::krpc::Stream<bool> has_fuel_stream();

    ::krpc::Stream<float> specific_impulse_stream();

    ::krpc::Stream<bool> roll_enabled_stream();

    ::krpc::Stream<bool> yaw_enabled_stream();

    ::krpc::Stream<float> max_vacuum_thrust_stream();

    ::krpc::Stream<bool> right_enabled_stream();

    ::krpc::Stream<bool> up_enabled_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Thruster>> thrusters_stream();

    ::krpc::Stream<bool> active_stream();

    ::krpc::Stream<std::vector<std::string>> propellants_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_torque_stream();

    ::krpc::Stream<std::map<std::string, float>> propellant_ratios_stream();

    ::krpc::Stream<float> kerbin_sea_level_specific_impulse_stream();

    ::krpc::Stream<bool> enabled_stream();

    ::krpc::Stream<float> max_thrust_stream();

    ::krpc::Stream<bool> pitch_enabled_stream();

    ::krpc::Stream<bool> forward_enabled_stream();
  };

  /**
   * A radiator. Obtained by calling SpaceCenter::Part::radiator.
   */
  class Radiator : public krpc::Object<Radiator> {
   public:
    explicit Radiator(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * For a deployable radiator, true if the radiator is extended.
     * If the radiator is not deployable, this is always true.
     */
    void set_deployed(bool value);

    /**
     * The current state of the radiator.
     *
     * A fixed radiator is always SpaceCenter::RadiatorState::extended.
     */
    SpaceCenter::RadiatorState state();

    /**
     * The part object for this radiator.
     */
    SpaceCenter::Part part();

    /**
     * For a deployable radiator, true if the radiator is extended.
     * If the radiator is not deployable, this is always true.
     */
    bool deployed();

    /**
     * Whether the radiator is deployable.
     */
    bool deployable();

    ::krpc::Stream<SpaceCenter::RadiatorState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> deployed_stream();

    ::krpc::Stream<bool> deployable_stream();
  };

  /**
   * A reaction wheel. Obtained by calling SpaceCenter::Part::reaction_wheel.
   */
  class ReactionWheel : public krpc::Object<ReactionWheel> {
   public:
    explicit ReactionWheel(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The maximum torque the reaction wheel can provide, is it active,
     * in the pitch, roll and yaw axes of the vessel, in Newton meters.
     * These axes correspond to the coordinate axes of the SpaceCenter::Vessel::reference_frame.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > max_torque();

    /**
     * Whether the reaction wheel is active.
     */
    void set_active(bool value);

    /**
     * Whether the reaction wheel is broken.
     */
    bool broken();

    /**
     * The part object for this reaction wheel.
     */
    SpaceCenter::Part part();

    /**
     * Whether the reaction wheel is active.
     */
    bool active();

    /**
     * The available torque in the pitch, roll and yaw axes of the vessel, in Newton meters.
     * These axes correspond to the coordinate axes of the SpaceCenter::Vessel::reference_frame.
     * Returns zero if the reaction wheel is inactive or broken.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_torque();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> max_torque_stream();

    ::krpc::Stream<bool> broken_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> active_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_torque_stream();
  };

  /**
   * Represents a reference frame for positions, rotations and
   * velocities. Contains:
   *
   * - The position of the origin.
   * - The directions of the x, y and z axes.
   * - The linear velocity of the frame.
   * - The angular velocity of the frame.
   *
   * This class does not contain any properties or methods. It is only
   * used as a parameter to other functions.
   */
  class ReferenceFrame : public krpc::Object<ReferenceFrame> {
   public:
    explicit ReferenceFrame(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Create a hybrid reference frame, which is a custom reference frame
     * whose components are inherited from other reference frames.
     * @param position The reference frame providing the position of the origin.
     * @param rotation The reference frame providing the orientation of the frame.
     * @param velocity The reference frame providing the linear velocity of the frame.
     * @param angularVelocity The reference frame providing the angular velocity of the frame.
     *
     * The position is required but all other reference frames are optional.
     * If omitted, they are set to the position reference frame.
     */
    static SpaceCenter::ReferenceFrame create_hybrid(Client& client, SpaceCenter::ReferenceFrame position, SpaceCenter::ReferenceFrame rotation, SpaceCenter::ReferenceFrame velocity, SpaceCenter::ReferenceFrame angular_velocity);

    /**
     * Create a relative reference frame.
     * @param referenceFrame The parent reference frame.
     * @param position The offset of the position of the origin.
     * @param rotation The rotation to apply to the parent frames rotation, as a quaternion. Defaults to zero.
     * @param velocity The linear velocity to offset the parent frame by. Defaults to zero.
     * @param angularVelocity The angular velocity to offset the parent frame by. Defaults to zero.
     */
    static SpaceCenter::ReferenceFrame create_relative(Client& client, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, std::tuple<double, double, double> velocity, std::tuple<double, double, double> angular_velocity);

    static ::krpc::Stream<SpaceCenter::ReferenceFrame> create_hybrid_stream(Client& client, SpaceCenter::ReferenceFrame position, SpaceCenter::ReferenceFrame rotation, SpaceCenter::ReferenceFrame velocity, SpaceCenter::ReferenceFrame angular_velocity);

    static ::krpc::Stream<SpaceCenter::ReferenceFrame> create_relative_stream(Client& client, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, std::tuple<double, double, double> velocity, std::tuple<double, double, double> angular_velocity);
  };

  /**
   * An individual resource stored within a part.
   * Created using methods in the SpaceCenter::Resources class.
   */
  class Resource : public krpc::Object<Resource> {
   public:
    explicit Resource(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The name of the resource.
     */
    std::string name();

    /**
     * The density of the resource, in kg/l.
     */
    float density();

    /**
     * The total amount of the resource that can be stored in the part.
     */
    float max();

    /**
     * Whether use of this resource is enabled.
     */
    bool enabled();

    /**
     * The amount of the resource that is currently stored in the part.
     */
    float amount();

    /**
     * The part containing the resource.
     */
    SpaceCenter::Part part();

    /**
     * Whether use of this resource is enabled.
     */
    void set_enabled(bool value);

    /**
     * The flow mode of the resource.
     */
    SpaceCenter::ResourceFlowMode flow_mode();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<float> density_stream();

    ::krpc::Stream<float> max_stream();

    ::krpc::Stream<bool> enabled_stream();

    ::krpc::Stream<float> amount_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<SpaceCenter::ResourceFlowMode> flow_mode_stream();
  };

  /**
   * A resource converter. Obtained by calling SpaceCenter::Part::resource_converter.
   */
  class ResourceConverter : public krpc::Object<ResourceConverter> {
   public:
    explicit ResourceConverter(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * True if the specified converter is active.
     * @param index Index of the converter.
     */
    bool active(google::protobuf::int32 index);

    /**
     * List of the names of resources consumed by the specified converter.
     * @param index Index of the converter.
     */
    std::vector<std::string> inputs(google::protobuf::int32 index);

    /**
     * The name of the specified converter.
     * @param index Index of the converter.
     */
    std::string name(google::protobuf::int32 index);

    /**
     * List of the names of resources produced by the specified converter.
     * @param index Index of the converter.
     */
    std::vector<std::string> outputs(google::protobuf::int32 index);

    /**
     * Start the specified converter.
     * @param index Index of the converter.
     */
    void start(google::protobuf::int32 index);

    /**
     * The state of the specified converter.
     * @param index Index of the converter.
     */
    SpaceCenter::ResourceConverterState state(google::protobuf::int32 index);

    /**
     * Status information for the specified converter.
     * This is the full status message shown in the in-game UI.
     * @param index Index of the converter.
     */
    std::string status_info(google::protobuf::int32 index);

    /**
     * Stop the specified converter.
     * @param index Index of the converter.
     */
    void stop(google::protobuf::int32 index);

    /**
     * The number of converters in the part.
     */
    google::protobuf::int32 count();

    /**
     * The part object for this converter.
     */
    SpaceCenter::Part part();

    ::krpc::Stream<bool> active_stream(google::protobuf::int32 index);

    ::krpc::Stream<std::vector<std::string>> inputs_stream(google::protobuf::int32 index);

    ::krpc::Stream<std::string> name_stream(google::protobuf::int32 index);

    ::krpc::Stream<std::vector<std::string>> outputs_stream(google::protobuf::int32 index);

    ::krpc::Stream<SpaceCenter::ResourceConverterState> state_stream(google::protobuf::int32 index);

    ::krpc::Stream<std::string> status_info_stream(google::protobuf::int32 index);

    ::krpc::Stream<google::protobuf::int32> count_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();
  };

  /**
   * A resource harvester (drill). Obtained by calling SpaceCenter::Part::resource_harvester.
   */
  class ResourceHarvester : public krpc::Object<ResourceHarvester> {
   public:
    explicit ResourceHarvester(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the harvester is deployed.
     */
    void set_deployed(bool value);

    /**
     * The rate at which the drill is extracting ore, in units per second.
     */
    float extraction_rate();

    /**
     * The thermal efficiency of the drill, as a percentage of its maximum.
     */
    float thermal_efficiency();

    /**
     * Whether the harvester is actively drilling.
     */
    void set_active(bool value);

    /**
     * The core temperature at which the drill will operate with peak efficiency, in Kelvin.
     */
    float optimum_core_temperature();

    /**
     * The core temperature of the drill, in Kelvin.
     */
    float core_temperature();

    /**
     * The state of the harvester.
     */
    SpaceCenter::ResourceHarvesterState state();

    /**
     * The part object for this harvester.
     */
    SpaceCenter::Part part();

    /**
     * Whether the harvester is actively drilling.
     */
    bool active();

    /**
     * Whether the harvester is deployed.
     */
    bool deployed();

    ::krpc::Stream<float> extraction_rate_stream();

    ::krpc::Stream<float> thermal_efficiency_stream();

    ::krpc::Stream<float> optimum_core_temperature_stream();

    ::krpc::Stream<float> core_temperature_stream();

    ::krpc::Stream<SpaceCenter::ResourceHarvesterState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> active_stream();

    ::krpc::Stream<bool> deployed_stream();
  };

  /**
   * Transfer resources between parts.
   */
  class ResourceTransfer : public krpc::Object<ResourceTransfer> {
   public:
    explicit ResourceTransfer(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Start transferring a resource transfer between a pair of parts. The transfer will move at most
     * maxAmount units of the resource, depending on how much of the resource is
     * available in the source part and how much storage is available in the destination part.
     * Use SpaceCenter::ResourceTransfer::complete to check if the transfer is complete.
     * Use SpaceCenter::ResourceTransfer::amount to see how much of the resource has been transferred.
     * @param fromPart The part to transfer to.
     * @param toPart The part to transfer from.
     * @param resource The name of the resource to transfer.
     * @param maxAmount The maximum amount of resource to transfer.
     */
    static SpaceCenter::ResourceTransfer start(Client& client, SpaceCenter::Part from_part, SpaceCenter::Part to_part, std::string resource, float max_amount);

    /**
     * The amount of the resource that has been transferred.
     */
    float amount();

    /**
     * Whether the transfer has completed.
     */
    bool complete();

    static ::krpc::Stream<SpaceCenter::ResourceTransfer> start_stream(Client& client, SpaceCenter::Part from_part, SpaceCenter::Part to_part, std::string resource, float max_amount);

    ::krpc::Stream<float> amount_stream();

    ::krpc::Stream<bool> complete_stream();
  };

  /**
   * Represents the collection of resources stored in a vessel, stage or part.
   * Created by calling SpaceCenter::Vessel::resources,
   * SpaceCenter::Vessel::resources_in_decouple_stage or
   * SpaceCenter::Part::resources.
   */
  class Resources : public krpc::Object<Resources> {
   public:
    explicit Resources(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Returns the amount of a resource that is currently stored.
     * @param name The name of the resource.
     */
    float amount(std::string name);

    /**
     * Check whether the named resource can be stored.
     * @param name The name of the resource.
     */
    bool has_resource(std::string name);

    /**
     * Returns the amount of a resource that can be stored.
     * @param name The name of the resource.
     */
    float max(std::string name);

    /**
     * All the individual resources with the given name that can be stored.
     */
    std::vector<SpaceCenter::Resource> with_resource(std::string name);

    /**
     * Returns the density of a resource, in kg/l.
     * @param name The name of the resource.
     */
    static float density(Client& client, std::string name);

    /**
     * Returns the flow mode of a resource.
     * @param name The name of the resource.
     */
    static SpaceCenter::ResourceFlowMode flow_mode(Client& client, std::string name);

    /**
     * Whether use of all the resources are enabled.
     *
     * This is true if all of the resources are enabled. If any of the resources are not enabled, this is false.
     */
    void set_enabled(bool value);

    /**
     * All the individual resources that can be stored.
     */
    std::vector<SpaceCenter::Resource> all();

    /**
     * Whether use of all the resources are enabled.
     *
     * This is true if all of the resources are enabled. If any of the resources are not enabled, this is false.
     */
    bool enabled();

    /**
     * A list of resource names that can be stored.
     */
    std::vector<std::string> names();

    ::krpc::Stream<float> amount_stream(std::string name);

    ::krpc::Stream<bool> has_resource_stream(std::string name);

    ::krpc::Stream<float> max_stream(std::string name);

    ::krpc::Stream<std::vector<SpaceCenter::Resource>> with_resource_stream(std::string name);

    static ::krpc::Stream<float> density_stream(Client& client, std::string name);

    static ::krpc::Stream<SpaceCenter::ResourceFlowMode> flow_mode_stream(Client& client, std::string name);

    ::krpc::Stream<std::vector<SpaceCenter::Resource>> all_stream();

    ::krpc::Stream<bool> enabled_stream();

    ::krpc::Stream<std::vector<std::string>> names_stream();
  };

  /**
   * Obtained by calling SpaceCenter::Experiment::data.
   */
  class ScienceData : public krpc::Object<ScienceData> {
   public:
    explicit ScienceData(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Data amount.
     */
    float data_amount();

    /**
     * Science value.
     */
    float science_value();

    /**
     * Transmit value.
     */
    float transmit_value();

    ::krpc::Stream<float> data_amount_stream();

    ::krpc::Stream<float> science_value_stream();

    ::krpc::Stream<float> transmit_value_stream();
  };

  /**
   * Obtained by calling SpaceCenter::Experiment::science_subject.
   */
  class ScienceSubject : public krpc::Object<ScienceSubject> {
   public:
    explicit ScienceSubject(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Multiplier for specific Celestial Body/Experiment Situation combination.
     */
    float subject_value();

    /**
     * Total science allowable for this subject.
     */
    float science_cap();

    /**
     * Title of science subject, displayed in science archives
     */
    std::string title();

    /**
     * Amount of science already earned from this subject, not updated until after transmission/recovery.
     */
    float science();

    /**
     * Diminishing value multiplier for decreasing the science value returned from repeated experiments.
     */
    float scientific_value();

    /**
     * Multiply science value by this to determine data amount in mits.
     */
    float data_scale();

    /**
     * Whether the experiment has been completed.
     */
    bool is_complete();

    ::krpc::Stream<float> subject_value_stream();

    ::krpc::Stream<float> science_cap_stream();

    ::krpc::Stream<std::string> title_stream();

    ::krpc::Stream<float> science_stream();

    ::krpc::Stream<float> scientific_value_stream();

    ::krpc::Stream<float> data_scale_stream();

    ::krpc::Stream<bool> is_complete_stream();
  };

  /**
   * A sensor, such as a thermometer. Obtained by calling SpaceCenter::Part::sensor.
   */
  class Sensor : public krpc::Object<Sensor> {
   public:
    explicit Sensor(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Whether the sensor is active.
     */
    bool active();

    /**
     * The part object for this sensor.
     */
    SpaceCenter::Part part();

    /**
     * The current value of the sensor.
     */
    std::string value();

    /**
     * Whether the sensor is active.
     */
    void set_active(bool value);

    ::krpc::Stream<bool> active_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<std::string> value_stream();
  };

  /**
   * A solar panel. Obtained by calling SpaceCenter::Part::solar_panel.
   */
  class SolarPanel : public krpc::Object<SolarPanel> {
   public:
    explicit SolarPanel(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * The current amount of energy being generated by the solar panel, in
     * units of charge per second.
     */
    float energy_flow();

    /**
     * Whether the solar panel is extended.
     */
    void set_deployed(bool value);

    /**
     * The current state of the solar panel.
     */
    SpaceCenter::SolarPanelState state();

    /**
     * The part object for this solar panel.
     */
    SpaceCenter::Part part();

    /**
     * The current amount of sunlight that is incident on the solar panel,
     * as a percentage. A value between 0 and 1.
     */
    float sun_exposure();

    /**
     * Whether the solar panel is extended.
     */
    bool deployed();

    ::krpc::Stream<float> energy_flow_stream();

    ::krpc::Stream<SpaceCenter::SolarPanelState> state_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<float> sun_exposure_stream();

    ::krpc::Stream<bool> deployed_stream();
  };

  /**
   * The component of an SpaceCenter::Engine or SpaceCenter::RCS part that generates thrust.
   * Can obtained by calling SpaceCenter::Engine::thrusters or SpaceCenter::RCS::thrusters.
   *
   * Engines can consist of multiple thrusters.
   * For example, the S3 KS-25x4 "Mammoth" has four rocket nozzels, and so consists of four thrusters.
   */
  class Thruster : public krpc::Object<Thruster> {
   public:
    explicit Thruster(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Position around which the gimbal pivots.
     */
    std::tuple<double, double, double> gimbal_position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The direction of the force generated by the thruster, when the engine is in its
     * initial position (no gimballing), in the given reference frame.
     * This is opposite to the direction in which the thruster expels propellant.
     * @param referenceFrame
     */
    std::tuple<double, double, double> initial_thrust_direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The position at which the thruster generates thrust, when the engine is in its
     * initial position (no gimballing), in the given reference frame.
     * @param referenceFrame
     *
     * This position can move when the gimbal rotates. This is because the thrust position and
     * gimbal position are not necessarily the same.
     */
    std::tuple<double, double, double> initial_thrust_position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The direction of the force generated by the thruster, in the given reference frame.
     * This is opposite to the direction in which the thruster expels propellant.
     * For gimballed engines, this takes into account the current rotation of the gimbal.
     * @param referenceFrame
     */
    std::tuple<double, double, double> thrust_direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The position at which the thruster generates thrust, in the given reference frame.
     * For gimballed engines, this takes into account the current rotation of the gimbal.
     * @param referenceFrame
     */
    std::tuple<double, double, double> thrust_position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * A reference frame that is fixed relative to the thruster and orientated with
     * its thrust direction (SpaceCenter::Thruster::thrust_direction).
     * For gimballed engines, this takes into account the current rotation of the gimbal.
     *
     * - The origin is at the position of thrust for this thruster (SpaceCenter::Thruster::thrust_position).
     * - The axes rotate with the thrust direction.
     *   This is the direction in which the thruster expels propellant, including any gimballing.
     * - The y-axis points along the thrust direction.
     * - The x-axis and z-axis are perpendicular to the thrust direction.
     */
    SpaceCenter::ReferenceFrame thrust_reference_frame();

    /**
     * The current gimbal angle in the pitch, roll and yaw axes.
     */
    std::tuple<double, double, double> gimbal_angle();

    /**
     * The SpaceCenter::Part that contains this thruster.
     */
    SpaceCenter::Part part();

    /**
     * Whether the thruster is gimballed.
     */
    bool gimballed();

    ::krpc::Stream<std::tuple<double, double, double>> gimbal_position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> initial_thrust_direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> initial_thrust_position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> thrust_direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> thrust_position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::ReferenceFrame> thrust_reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> gimbal_angle_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<bool> gimballed_stream();
  };

  /**
   * These objects are used to interact with vessels in KSP. This includes getting
   * orbital and flight data, manipulating control inputs and managing resources.
   * Created using SpaceCenter::active_vessel or SpaceCenter::vessels.
   */
  class Vessel : public krpc::Object<Vessel> {
   public:
    explicit Vessel(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Returns the angular velocity of the vessel in the given reference frame. The magnitude of the returned
     * vector is the rotational speed in radians per second, and the direction of the vector indicates the
     * axis of rotation (using the right hand rule).
     * @param referenceFrame
     */
    std::tuple<double, double, double> angular_velocity(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * The axis-aligned bounding box of the vessel in the given reference frame.
     * Returns the minimum and maximum vertices of the box.
     * @param referenceFrame
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > bounding_box(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the direction in which the vessel is pointing, as a unit vector, in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> direction(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns a SpaceCenter::Flight object that can be used to get flight
     * telemetry for the vessel, in the specified reference frame.
     * @param referenceFrame Reference frame. Defaults to the vessel's surface reference frame (SpaceCenter::Vessel::surface_reference_frame).
     */
    SpaceCenter::Flight flight(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the position vector of the center of mass of the vessel in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> position(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Recover the vessel.
     */
    void recover();

    /**
     * Returns a SpaceCenter::Resources object, that can used to get
     * information about resources stored in a given stage.
     * @param stage Get resources for parts that are decoupled in this stage.
     * @param cumulative When false, returns the resources for parts
     * decoupled in just the given stage. When true returns the resources decoupled in
     * the given stage and all subsequent stages combined.
     */
    SpaceCenter::Resources resources_in_decouple_stage(google::protobuf::int32 stage, bool cumulative);

    /**
     * Returns the rotation of the center of mass of the vessel in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double, double> rotation(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns the velocity vector of the center of mass of the vessel in the given reference frame.
     * @param referenceFrame
     */
    std::tuple<double, double, double> velocity(SpaceCenter::ReferenceFrame reference_frame);

    /**
     * Returns a SpaceCenter::Control object that can be used to manipulate
     * the vessel's control inputs. For example, its pitch/yaw/roll controls,
     * RCS and thrust.
     */
    SpaceCenter::Control control();

    /**
     * The maximum torque that the currently active RCS thrusters can generate.
     * Returns the torques in N.m around each of the coordinate axes of the
     * vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * These axes are equivalent to the pitch, roll and yaw axes of the vessel.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_rcs_torque();

    /**
     * The maximum torque that the currently active and powered reaction wheels can generate.
     * Returns the torques in N.m around each of the coordinate axes of the
     * vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * These axes are equivalent to the pitch, roll and yaw axes of the vessel.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_reaction_wheel_torque();

    /**
     * The combined specific impulse of all active engines, in seconds. This is computed using the formula
     * <a href="http://wiki.kerbalspaceprogram.com/wiki/Specific_impulse#Multiple_engines">described here</a>.
     */
    float specific_impulse();

    /**
     * The maximum torque that parts (excluding reaction wheels, gimballed engines, RCS and control surfaces) can generate.
     * Returns the torques in N.m around each of the coordinate axes of the
     * vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * These axes are equivalent to the pitch, roll and yaw axes of the vessel.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_other_torque();

    /**
     * The inertia tensor of the vessel around its center of mass, in the vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * Returns the 3x3 matrix as a list of elements, in row-major order.
     */
    std::vector<double> inertia_tensor();

    /**
     * The name of the biome the vessel is currently in.
     */
    std::string biome();

    /**
     * The reference frame that is fixed relative to the vessel, and orientated with the velocity
     * vector of the vessel relative to the surface of the body being orbited.
     *
     * - The origin is at the center of mass of the vessel.
     * - The axes rotate with the vessel's velocity vector.
     * - The y-axis points in the direction of the vessel's velocity vector,
     *   relative to the surface of the body being orbited.
     * - The z-axis is in the plane of the
     *   <a href="https://en.wikipedia.org/wiki/Horizon">astronomical horizon</a>.
     * - The x-axis is orthogonal to the other two axes.
     */
    SpaceCenter::ReferenceFrame surface_velocity_reference_frame();

    /**
     * Gets the total available thrust that can be produced by the vessel's
     * active engines, in Newtons. This is computed by summing
     * SpaceCenter::Engine::available_thrust for every active engine in the vessel.
     */
    float available_thrust();

    /**
     * A SpaceCenter::Parts object, that can used to interact with the parts that make up this vessel.
     */
    SpaceCenter::Parts parts();

    /**
     * The reference frame that is fixed relative to the vessel, and orientated with the vessels
     * orbital prograde/normal/radial directions.
     *
     * - The origin is at the center of mass of the vessel.
     * - The axes rotate with the orbital prograde/normal/radial directions.
     * - The x-axis points in the orbital anti-radial direction.
     * - The y-axis points in the orbital prograde direction.
     * - The z-axis points in the orbital normal direction.
     *
     * Be careful not to confuse this with 'orbit' mode on the navball.
     */
    SpaceCenter::ReferenceFrame orbital_reference_frame();

    /**
     * An SpaceCenter::AutoPilot object, that can be used to perform
     * simple auto-piloting of the vessel.
     */
    SpaceCenter::AutoPilot auto_pilot();

    /**
     * The total mass of the vessel, including resources, in kg.
     */
    float mass();

    /**
     * The type of the vessel.
     */
    SpaceCenter::VesselType type();

    /**
     * A SpaceCenter::Resources object, that can used to get information
     * about resources stored in the vessel.
     */
    SpaceCenter::Resources resources();

    /**
     * The reference frame that is fixed relative to the vessel, and orientated with the vessel.
     *
     * - The origin is at the center of mass of the vessel.
     * - The axes rotate with the vessel.
     * - The x-axis points out to the right of the vessel.
     * - The y-axis points in the forward direction of the vessel.
     * - The z-axis points out of the bottom off the vessel.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * The moment of inertia of the vessel around its center of mass in kg.m^2.
     * The inertia values are around the pitch, roll and yaw directions respectively.
     * This corresponds to the vessels reference frame (SpaceCenter::Vessel::reference_frame).
     */
    std::tuple<double, double, double> moment_of_inertia();

    /**
     * The total maximum thrust that can be produced by the vessel's active
     * engines when the vessel is in a vacuum, in Newtons. This is computed by
     * summing SpaceCenter::Engine::max_vacuum_thrust for every active engine.
     */
    float max_vacuum_thrust();

    /**
     * The type of the vessel.
     */
    void set_type(SpaceCenter::VesselType value);

    /**
     * The mission elapsed time in seconds.
     */
    double met();

    /**
     * The situation the vessel is in.
     */
    SpaceCenter::VesselSituation situation();

    /**
     * The total thrust currently being produced by the vessel's engines, in
     * Newtons. This is computed by summing SpaceCenter::Engine::thrust for
     * every engine in the vessel.
     */
    float thrust();

    /**
     * The maximum torque that the vessel generate. Includes contributions from reaction wheels,
     * RCS, gimballed engines and aerodynamic control surfaces.
     * Returns the torques in N.m around each of the coordinate axes of the
     * vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * These axes are equivalent to the pitch, roll and yaw axes of the vessel.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_torque();

    /**
     * The name of the vessel.
     */
    void set_name(std::string value);

    /**
     * The name of the vessel.
     */
    std::string name();

    /**
     * The combined specific impulse of all active engines at sea level on Kerbin, in seconds.
     * This is computed using the formula
     * <a href="http://wiki.kerbalspaceprogram.com/wiki/Specific_impulse#Multiple_engines">described here</a>.
     */
    float kerbin_sea_level_specific_impulse();

    /**
     * The current orbit of the vessel.
     */
    SpaceCenter::Orbit orbit();

    /**
     * The maximum torque that the currently active and gimballed engines can generate.
     * Returns the torques in N.m around each of the coordinate axes of the
     * vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * These axes are equivalent to the pitch, roll and yaw axes of the vessel.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_engine_torque();

    /**
     * The reference frame that is fixed relative to the vessel, and orientated with the surface
     * of the body being orbited.
     *
     * - The origin is at the center of mass of the vessel.
     * - The axes rotate with the north and up directions on the surface of the body.
     * - The x-axis points in the <a href="https://en.wikipedia.org/wiki/Zenith">zenith</a>
     *   direction (upwards, normal to the body being orbited, from the center of the body towards the center of
     *   mass of the vessel).
     * - The y-axis points northwards towards the
     *   <a href="https://en.wikipedia.org/wiki/Horizon">astronomical horizon</a> (north, and tangential to the
     *   surface of the body -- the direction in which a compass would point when on the surface).
     * - The z-axis points eastwards towards the
     *   <a href="https://en.wikipedia.org/wiki/Horizon">astronomical horizon</a> (east, and tangential to the
     *   surface of the body -- east on a compass when on the surface).
     *
     * Be careful not to confuse this with 'surface' mode on the navball.
     */
    SpaceCenter::ReferenceFrame surface_reference_frame();

    /**
     * The combined vacuum specific impulse of all active engines, in seconds. This is computed using the formula
     * <a href="http://wiki.kerbalspaceprogram.com/wiki/Specific_impulse#Multiple_engines">described here</a>.
     */
    float vacuum_specific_impulse();

    /**
     * The maximum torque that the aerodynamic control surfaces can generate.
     * Returns the torques in N.m around each of the coordinate axes of the
     * vessels reference frame (SpaceCenter::Vessel::reference_frame).
     * These axes are equivalent to the pitch, roll and yaw axes of the vessel.
     */
    std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > available_control_surface_torque();

    /**
     * The total maximum thrust that can be produced by the vessel's active
     * engines, in Newtons. This is computed by summing
     * SpaceCenter::Engine::max_thrust for every active engine.
     */
    float max_thrust();

    /**
     * The total mass of the vessel, excluding resources, in kg.
     */
    float dry_mass();

    /**
     * Whether the vessel is recoverable.
     */
    bool recoverable();

    ::krpc::Stream<std::tuple<double, double, double>> angular_velocity_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> bounding_box_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> direction_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::Flight> flight_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> position_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::Resources> resources_in_decouple_stage_stream(google::protobuf::int32 stage, bool cumulative);

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<std::tuple<double, double, double>> velocity_stream(SpaceCenter::ReferenceFrame reference_frame);

    ::krpc::Stream<SpaceCenter::Control> control_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_rcs_torque_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_reaction_wheel_torque_stream();

    ::krpc::Stream<float> specific_impulse_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_other_torque_stream();

    ::krpc::Stream<std::vector<double>> inertia_tensor_stream();

    ::krpc::Stream<std::string> biome_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> surface_velocity_reference_frame_stream();

    ::krpc::Stream<float> available_thrust_stream();

    ::krpc::Stream<SpaceCenter::Parts> parts_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> orbital_reference_frame_stream();

    ::krpc::Stream<SpaceCenter::AutoPilot> auto_pilot_stream();

    ::krpc::Stream<float> mass_stream();

    ::krpc::Stream<SpaceCenter::VesselType> type_stream();

    ::krpc::Stream<SpaceCenter::Resources> resources_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> moment_of_inertia_stream();

    ::krpc::Stream<float> max_vacuum_thrust_stream();

    ::krpc::Stream<double> met_stream();

    ::krpc::Stream<SpaceCenter::VesselSituation> situation_stream();

    ::krpc::Stream<float> thrust_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_torque_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<float> kerbin_sea_level_specific_impulse_stream();

    ::krpc::Stream<SpaceCenter::Orbit> orbit_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_engine_torque_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> surface_reference_frame_stream();

    ::krpc::Stream<float> vacuum_specific_impulse_stream();

    ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> available_control_surface_torque_stream();

    ::krpc::Stream<float> max_thrust_stream();

    ::krpc::Stream<float> dry_mass_stream();

    ::krpc::Stream<bool> recoverable_stream();
  };

  /**
   * Represents a waypoint. Can be created using SpaceCenter::WaypointManager::add_waypoint.
   */
  class Waypoint : public krpc::Object<Waypoint> {
   public:
    explicit Waypoint(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Removes the waypoint.
     */
    void remove();

    /**
     * Celestial body the waypoint is attached to.
     */
    void set_body(SpaceCenter::CelestialBody value);

    /**
     * The seed of the icon color. See SpaceCenter::WaypointManager::colors for example colors.
     */
    google::protobuf::int32 color();

    /**
     * The icon of the waypoint.
     */
    void set_icon(std::string value);

    /**
     * True if waypoint is a point near or on the body rather than high in orbit.
     */
    bool near_surface();

    /**
     * The longitude of the waypoint.
     */
    void set_longitude(double value);

    /**
     * The integer index of this waypoint amongst its cluster of sibling waypoints.
     * In other words, when you have a cluster of waypoints called "Somewhere Alpha", "Somewhere Beta", and "Somewhere Gamma",
     * then the alpha site has index 0, the beta site has index 1 and the gamma site has index 2.
     * When SpaceCenter::Waypoint::clustered is false, this value is zero but meaningless.
     */
    google::protobuf::int32 index();

    /**
     * The altitude of the waypoint above sea level, in meters.
     */
    double mean_altitude();

    /**
     * True if waypoint is actually glued to the ground.
     */
    bool grounded();

    /**
     * Whether the waypoint belongs to a contract.
     */
    bool has_contract();

    /**
     * The altitude of the waypoint above the surface of the body or sea level, whichever is closer, in meters.
     */
    double surface_altitude();

    /**
     * The latitude of the waypoint.
     */
    double latitude();

    /**
     * The icon of the waypoint.
     */
    std::string icon();

    /**
     * The altitude of the waypoint above the surface of the body, in meters. When over water, this is the altitude above the sea floor.
     */
    double bedrock_altitude();

    /**
     * Celestial body the waypoint is attached to.
     */
    SpaceCenter::CelestialBody body();

    /**
     * The altitude of the waypoint above the surface of the body or sea level, whichever is closer, in meters.
     */
    void set_surface_altitude(double value);

    /**
     * True if this waypoint is part of a set of clustered waypoints with greek letter names appended (Alpha, Beta, Gamma, etc).
     * If true, there is a one-to-one correspondence with the greek letter name and the SpaceCenter::Waypoint::index.
     */
    bool clustered();

    /**
     * The id of the associated contract.
     * Returns 0 if the waypoint does not belong to a contract.
     */
    google::protobuf::int64 contract_id();

    /**
     * The altitude of the waypoint above the surface of the body, in meters. When over water, this is the altitude above the sea floor.
     */
    void set_bedrock_altitude(double value);

    /**
     * Name of the waypoint as it appears on the map and the contract.
     */
    void set_name(std::string value);

    /**
     * Name of the waypoint as it appears on the map and the contract.
     */
    std::string name();

    /**
     * The longitude of the waypoint.
     */
    double longitude();

    /**
     * The latitude of the waypoint.
     */
    void set_latitude(double value);

    /**
     * The altitude of the waypoint above sea level, in meters.
     */
    void set_mean_altitude(double value);

    /**
     * The seed of the icon color. See SpaceCenter::WaypointManager::colors for example colors.
     */
    void set_color(google::protobuf::int32 value);

    ::krpc::Stream<google::protobuf::int32> color_stream();

    ::krpc::Stream<bool> near_surface_stream();

    ::krpc::Stream<google::protobuf::int32> index_stream();

    ::krpc::Stream<double> mean_altitude_stream();

    ::krpc::Stream<bool> grounded_stream();

    ::krpc::Stream<bool> has_contract_stream();

    ::krpc::Stream<double> surface_altitude_stream();

    ::krpc::Stream<double> latitude_stream();

    ::krpc::Stream<std::string> icon_stream();

    ::krpc::Stream<double> bedrock_altitude_stream();

    ::krpc::Stream<SpaceCenter::CelestialBody> body_stream();

    ::krpc::Stream<bool> clustered_stream();

    ::krpc::Stream<google::protobuf::int64> contract_id_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<double> longitude_stream();
  };

  /**
   * Waypoints are the location markers you can see on the map view showing you where contracts are targeted for.
   * With this structure, you can obtain coordinate data for the locations of these waypoints.
   * Obtained by calling SpaceCenter::waypoint_manager.
   */
  class WaypointManager : public krpc::Object<WaypointManager> {
   public:
    explicit WaypointManager(Client* client = nullptr, google::protobuf::uint64 id = 0);

    /**
     * Creates a waypoint at the given position at ground level, and returns a
     * SpaceCenter::Waypoint object that can be used to modify it.
     * @param latitude Latitude of the waypoint.
     * @param longitude Longitude of the waypoint.
     * @param body Celestial body the waypoint is attached to.
     * @param name Name of the waypoint.
     * @return
     */
    SpaceCenter::Waypoint add_waypoint(double latitude, double longitude, SpaceCenter::CelestialBody body, std::string name);

    /**
     * An example map of known color - seed pairs.
     * Any other integers may be used as seed.
     */
    std::map<std::string, google::protobuf::int32> colors();

    /**
     * A list of all existing waypoints.
     */
    std::vector<SpaceCenter::Waypoint> waypoints();

    /**
     * Returns all available icons (from "GameData/Squad/Contracts/Icons/").
     */
    std::vector<std::string> icons();

    ::krpc::Stream<SpaceCenter::Waypoint> add_waypoint_stream(double latitude, double longitude, SpaceCenter::CelestialBody body, std::string name);

    ::krpc::Stream<std::map<std::string, google::protobuf::int32>> colors_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Waypoint>> waypoints_stream();

    ::krpc::Stream<std::vector<std::string>> icons_stream();
  };
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::SpaceCenter::CameraMode& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::CargoBayState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::DockingPortState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::LandingGearState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::LandingLegState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::ParachuteState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::RadiatorState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::ResourceConverterState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::ResourceFlowMode& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::ResourceHarvesterState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::SASMode& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::SolarPanelState& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::SpeedMode& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::VesselSituation& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::VesselType& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

  inline std::string encode(const services::SpaceCenter::WarpMode& value) {
    return krpc::encoder::encode(static_cast<google::protobuf::int32>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::SpaceCenter::CameraMode& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::CameraMode>(x);
  }

  inline void decode(services::SpaceCenter::CargoBayState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::CargoBayState>(x);
  }

  inline void decode(services::SpaceCenter::DockingPortState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::DockingPortState>(x);
  }

  inline void decode(services::SpaceCenter::LandingGearState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::LandingGearState>(x);
  }

  inline void decode(services::SpaceCenter::LandingLegState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::LandingLegState>(x);
  }

  inline void decode(services::SpaceCenter::ParachuteState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::ParachuteState>(x);
  }

  inline void decode(services::SpaceCenter::RadiatorState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::RadiatorState>(x);
  }

  inline void decode(services::SpaceCenter::ResourceConverterState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::ResourceConverterState>(x);
  }

  inline void decode(services::SpaceCenter::ResourceFlowMode& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::ResourceFlowMode>(x);
  }

  inline void decode(services::SpaceCenter::ResourceHarvesterState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::ResourceHarvesterState>(x);
  }

  inline void decode(services::SpaceCenter::SASMode& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::SASMode>(x);
  }

  inline void decode(services::SpaceCenter::SolarPanelState& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::SolarPanelState>(x);
  }

  inline void decode(services::SpaceCenter::SpeedMode& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::SpeedMode>(x);
  }

  inline void decode(services::SpaceCenter::VesselSituation& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::VesselSituation>(x);
  }

  inline void decode(services::SpaceCenter::VesselType& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::VesselType>(x);
  }

  inline void decode(services::SpaceCenter::WarpMode& value, const std::string& data, Client* client) {
    google::protobuf::int32 x;
    decode(x, data, client);
    value = static_cast<services::SpaceCenter::WarpMode>(x);
  }

}  // namespace decoder

namespace services {

inline SpaceCenter::SpaceCenter(Client* client):
  Service(client) {}

inline bool SpaceCenter::can_rails_warp_at(google::protobuf::int32 factor = 1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(factor));
  std::string _data = this->_client->invoke("SpaceCenter", "CanRailsWarpAt", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::clear_target() {
  this->_client->invoke("SpaceCenter", "ClearTarget");
}

inline void SpaceCenter::launch_vessel(std::string craft_directory, std::string name, std::string launch_site) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(craft_directory));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(launch_site));
  this->_client->invoke("SpaceCenter", "LaunchVessel", _args);
}

inline void SpaceCenter::launch_vessel_from_sph(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  this->_client->invoke("SpaceCenter", "LaunchVesselFromSPH", _args);
}

inline void SpaceCenter::launch_vessel_from_vab(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  this->_client->invoke("SpaceCenter", "LaunchVesselFromVAB", _args);
}

inline std::vector<std::string> SpaceCenter::launchable_vessels(std::string craft_directory) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(craft_directory));
  std::string _data = this->_client->invoke("SpaceCenter", "LaunchableVessels", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::load(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  this->_client->invoke("SpaceCenter", "Load", _args);
}

inline void SpaceCenter::quickload() {
  this->_client->invoke("SpaceCenter", "Quickload");
}

inline void SpaceCenter::quicksave() {
  this->_client->invoke("SpaceCenter", "Quicksave");
}

inline void SpaceCenter::save(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  this->_client->invoke("SpaceCenter", "Save", _args);
}

inline std::tuple<double, double, double> SpaceCenter::transform_direction(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  std::string _data = this->_client->invoke("SpaceCenter", "TransformDirection", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::transform_position(std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  std::string _data = this->_client->invoke("SpaceCenter", "TransformPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double, double> SpaceCenter::transform_rotation(std::tuple<double, double, double, double> rotation, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  std::string _data = this->_client->invoke("SpaceCenter", "TransformRotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::transform_velocity(std::tuple<double, double, double> position, std::tuple<double, double, double> velocity, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(velocity));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  std::string _data = this->_client->invoke("SpaceCenter", "TransformVelocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::warp_to(double ut, float max_rails_rate = 100000.0, float max_physics_rate = 2.0) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(ut));
  _args.push_back(encoder::encode(max_rails_rate));
  _args.push_back(encoder::encode(max_physics_rate));
  this->_client->invoke("SpaceCenter", "WarpTo", _args);
}

inline void SpaceCenter::set_target_docking_port(SpaceCenter::DockingPort value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "set_TargetDockingPort", _args);
}

inline SpaceCenter::Vessel SpaceCenter::active_vessel() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_ActiveVessel");
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline google::protobuf::int32 SpaceCenter::rails_warp_factor() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_RailsWarpFactor");
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::WarpMode SpaceCenter::warp_mode() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_WarpMode");
  SpaceCenter::WarpMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::set_target_vessel(SpaceCenter::Vessel value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "set_TargetVessel", _args);
}

inline SpaceCenter::WaypointManager SpaceCenter::waypoint_manager() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_WaypointManager");
  SpaceCenter::WaypointManager _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::DockingPort SpaceCenter::target_docking_port() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_TargetDockingPort");
  SpaceCenter::DockingPort _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::warp_factor() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_WarpFactor");
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::set_physics_warp_factor(google::protobuf::int32 value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "set_PhysicsWarpFactor", _args);
}

inline std::vector<SpaceCenter::Vessel> SpaceCenter::vessels() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_Vessels");
  std::vector<SpaceCenter::Vessel> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline google::protobuf::int32 SpaceCenter::maximum_rails_warp_factor() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_MaximumRailsWarpFactor");
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Camera SpaceCenter::camera() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_Camera");
  SpaceCenter::Camera _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::far_available() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_FARAvailable");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel SpaceCenter::target_vessel() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_TargetVessel");
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CelestialBody SpaceCenter::target_body() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_TargetBody");
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::warp_rate() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_WarpRate");
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::set_active_vessel(SpaceCenter::Vessel value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "set_ActiveVessel", _args);
}

inline google::protobuf::int32 SpaceCenter::physics_warp_factor() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_PhysicsWarpFactor");
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::set_target_body(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "set_TargetBody", _args);
}

inline double SpaceCenter::g() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_G");
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::ut() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_UT");
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::set_rails_warp_factor(google::protobuf::int32 value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "set_RailsWarpFactor", _args);
}

inline std::map<std::string, SpaceCenter::CelestialBody> SpaceCenter::bodies() {
  std::string _data = this->_client->invoke("SpaceCenter", "get_Bodies");
  std::map<std::string, SpaceCenter::CelestialBody> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> SpaceCenter::can_rails_warp_at_stream(google::protobuf::int32 factor = 1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(factor));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "CanRailsWarpAt", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::launchable_vessels_stream(std::string craft_directory) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(craft_directory));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "LaunchableVessels", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::transform_direction_stream(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "TransformDirection", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::transform_position_stream(std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "TransformPosition", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> SpaceCenter::transform_rotation_stream(std::tuple<double, double, double, double> rotation, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("SpaceCenter", "TransformRotation", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::transform_velocity_stream(std::tuple<double, double, double> position, std::tuple<double, double, double> velocity, SpaceCenter::ReferenceFrame from, SpaceCenter::ReferenceFrame to) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(velocity));
  _args.push_back(encoder::encode(from));
  _args.push_back(encoder::encode(to));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "TransformVelocity", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> SpaceCenter::active_vessel_stream() {
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("SpaceCenter", "get_ActiveVessel"));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::rails_warp_factor_stream() {
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "get_RailsWarpFactor"));
}

inline ::krpc::Stream<SpaceCenter::WarpMode> SpaceCenter::warp_mode_stream() {
  return ::krpc::Stream<SpaceCenter::WarpMode>(this->_client, this->_client->request("SpaceCenter", "get_WarpMode"));
}

inline ::krpc::Stream<SpaceCenter::WaypointManager> SpaceCenter::waypoint_manager_stream() {
  return ::krpc::Stream<SpaceCenter::WaypointManager>(this->_client, this->_client->request("SpaceCenter", "get_WaypointManager"));
}

inline ::krpc::Stream<SpaceCenter::DockingPort> SpaceCenter::target_docking_port_stream() {
  return ::krpc::Stream<SpaceCenter::DockingPort>(this->_client, this->_client->request("SpaceCenter", "get_TargetDockingPort"));
}

inline ::krpc::Stream<float> SpaceCenter::warp_factor_stream() {
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "get_WarpFactor"));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Vessel>> SpaceCenter::vessels_stream() {
  return ::krpc::Stream<std::vector<SpaceCenter::Vessel>>(this->_client, this->_client->request("SpaceCenter", "get_Vessels"));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::maximum_rails_warp_factor_stream() {
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "get_MaximumRailsWarpFactor"));
}

inline ::krpc::Stream<SpaceCenter::Camera> SpaceCenter::camera_stream() {
  return ::krpc::Stream<SpaceCenter::Camera>(this->_client, this->_client->request("SpaceCenter", "get_Camera"));
}

inline ::krpc::Stream<bool> SpaceCenter::far_available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "get_FARAvailable"));
}

inline ::krpc::Stream<SpaceCenter::Vessel> SpaceCenter::target_vessel_stream() {
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("SpaceCenter", "get_TargetVessel"));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> SpaceCenter::target_body_stream() {
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->request("SpaceCenter", "get_TargetBody"));
}

inline ::krpc::Stream<float> SpaceCenter::warp_rate_stream() {
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "get_WarpRate"));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::physics_warp_factor_stream() {
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "get_PhysicsWarpFactor"));
}

inline ::krpc::Stream<double> SpaceCenter::g_stream() {
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "get_G"));
}

inline ::krpc::Stream<double> SpaceCenter::ut_stream() {
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "get_UT"));
}

inline ::krpc::Stream<std::map<std::string, SpaceCenter::CelestialBody>> SpaceCenter::bodies_stream() {
  return ::krpc::Stream<std::map<std::string, SpaceCenter::CelestialBody>>(this->_client, this->_client->request("SpaceCenter", "get_Bodies"));
}

inline SpaceCenter::AutoPilot::AutoPilot(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::AutoPilot", id) {}

inline void SpaceCenter::AutoPilot::disengage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "AutoPilot_Disengage", _args);
}

inline void SpaceCenter::AutoPilot::engage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "AutoPilot_Engage", _args);
}

inline void SpaceCenter::AutoPilot::target_pitch_and_heading(float pitch, float heading) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(pitch));
  _args.push_back(encoder::encode(heading));
  this->_client->invoke("SpaceCenter", "AutoPilot_TargetPitchAndHeading", _args);
}

inline void SpaceCenter::AutoPilot::wait() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "AutoPilot_Wait", _args);
}

inline float SpaceCenter::AutoPilot::heading_error() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_HeadingError", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::time_to_peak() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_TimeToPeak", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::attenuation_angle() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_AttenuationAngle", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::overshoot() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_Overshoot", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_overshoot(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_Overshoot", _args);
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::target_direction() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_TargetDirection", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_time_to_peak(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_TimeToPeak", _args);
}

inline bool SpaceCenter::AutoPilot::sas() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_SAS", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::AutoPilot::target_heading() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_TargetHeading", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_deceleration_time(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_DecelerationTime", _args);
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::yaw_pid_gains() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_YawPIDGains", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_roll_pid_gains(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_RollPIDGains", _args);
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::roll_pid_gains() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_RollPIDGains", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::AutoPilot::target_pitch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_TargetPitch", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_roll_threshold(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_RollThreshold", _args);
}

inline SpaceCenter::SASMode SpaceCenter::AutoPilot::sas_mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_SASMode", _args);
  SpaceCenter::SASMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::AutoPilot::roll_error() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_RollError", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_target_heading(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_TargetHeading", _args);
}

inline SpaceCenter::ReferenceFrame SpaceCenter::AutoPilot::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::stopping_time() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_StoppingTime", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::AutoPilot::auto_tune() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_AutoTune", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::deceleration_time() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_DecelerationTime", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_pitch_pid_gains(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_PitchPIDGains", _args);
}

inline void SpaceCenter::AutoPilot::set_target_pitch(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_TargetPitch", _args);
}

inline void SpaceCenter::AutoPilot::set_yaw_pid_gains(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_YawPIDGains", _args);
}

inline double SpaceCenter::AutoPilot::roll_threshold() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_RollThreshold", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_target_roll(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_TargetRoll", _args);
}

inline void SpaceCenter::AutoPilot::set_sas_mode(SpaceCenter::SASMode value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_SASMode", _args);
}

inline void SpaceCenter::AutoPilot::set_target_direction(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_TargetDirection", _args);
}

inline float SpaceCenter::AutoPilot::target_roll() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_TargetRoll", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::AutoPilot::pitch_pid_gains() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_PitchPIDGains", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_ReferenceFrame", _args);
}

inline float SpaceCenter::AutoPilot::pitch_error() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_PitchError", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::AutoPilot::set_stopping_time(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_StoppingTime", _args);
}

inline void SpaceCenter::AutoPilot::set_auto_tune(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_AutoTune", _args);
}

inline void SpaceCenter::AutoPilot::set_attenuation_angle(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_AttenuationAngle", _args);
}

inline void SpaceCenter::AutoPilot::set_sas(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "AutoPilot_set_SAS", _args);
}

inline float SpaceCenter::AutoPilot::error() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "AutoPilot_get_Error", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::heading_error_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_HeadingError", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::time_to_peak_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_TimeToPeak", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::attenuation_angle_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_AttenuationAngle", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::overshoot_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_Overshoot", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::target_direction_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_TargetDirection", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::AutoPilot::sas_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_SAS", _args));
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::target_heading_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_TargetHeading", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::yaw_pid_gains_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_YawPIDGains", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::roll_pid_gains_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_RollPIDGains", _args));
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::target_pitch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_TargetPitch", _args));
}

inline ::krpc::Stream<SpaceCenter::SASMode> SpaceCenter::AutoPilot::sas_mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::SASMode>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_SASMode", _args));
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::roll_error_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_RollError", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::AutoPilot::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::stopping_time_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_StoppingTime", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::AutoPilot::auto_tune_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_AutoTune", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::deceleration_time_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_DecelerationTime", _args));
}

inline ::krpc::Stream<double> SpaceCenter::AutoPilot::roll_threshold_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_RollThreshold", _args));
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::target_roll_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_TargetRoll", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::AutoPilot::pitch_pid_gains_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_PitchPIDGains", _args));
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::pitch_error_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_PitchError", _args));
}

inline ::krpc::Stream<float> SpaceCenter::AutoPilot::error_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "AutoPilot_get_Error", _args));
}

inline SpaceCenter::Camera::Camera(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Camera", id) {}

inline float SpaceCenter::Camera::distance() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_Distance", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Camera::set_focussed_body(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_FocussedBody", _args);
}

inline void SpaceCenter::Camera::set_heading(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_Heading", _args);
}

inline void SpaceCenter::Camera::set_mode(SpaceCenter::CameraMode value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_Mode", _args);
}

inline void SpaceCenter::Camera::set_pitch(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_Pitch", _args);
}

inline void SpaceCenter::Camera::set_focussed_node(SpaceCenter::Node value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_FocussedNode", _args);
}

inline float SpaceCenter::Camera::max_pitch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_MaxPitch", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Camera::set_distance(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_Distance", _args);
}

inline float SpaceCenter::Camera::min_pitch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_MinPitch", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Camera::default_distance() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_DefaultDistance", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Node SpaceCenter::Camera::focussed_node() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_FocussedNode", _args);
  SpaceCenter::Node _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Camera::set_focussed_vessel(SpaceCenter::Vessel value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Camera_set_FocussedVessel", _args);
}

inline SpaceCenter::CameraMode SpaceCenter::Camera::mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_Mode", _args);
  SpaceCenter::CameraMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel SpaceCenter::Camera::focussed_vessel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_FocussedVessel", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Camera::pitch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_Pitch", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Camera::max_distance() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_MaxDistance", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CelestialBody SpaceCenter::Camera::focussed_body() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_FocussedBody", _args);
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Camera::heading() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_Heading", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Camera::min_distance() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Camera_get_MinDistance", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::Camera::distance_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_Distance", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::max_pitch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_MaxPitch", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::min_pitch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_MinPitch", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::default_distance_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_DefaultDistance", _args));
}

inline ::krpc::Stream<SpaceCenter::Node> SpaceCenter::Camera::focussed_node_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Node>(this->_client, this->_client->request("SpaceCenter", "Camera_get_FocussedNode", _args));
}

inline ::krpc::Stream<SpaceCenter::CameraMode> SpaceCenter::Camera::mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CameraMode>(this->_client, this->_client->request("SpaceCenter", "Camera_get_Mode", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> SpaceCenter::Camera::focussed_vessel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("SpaceCenter", "Camera_get_FocussedVessel", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::pitch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_Pitch", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::max_distance_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_MaxDistance", _args));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> SpaceCenter::Camera::focussed_body_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->request("SpaceCenter", "Camera_get_FocussedBody", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::heading_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_Heading", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Camera::min_distance_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Camera_get_MinDistance", _args));
}

inline SpaceCenter::CargoBay::CargoBay(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::CargoBay", id) {}

inline SpaceCenter::Part SpaceCenter::CargoBay::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CargoBay_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::CargoBay::set_open(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "CargoBay_set_Open", _args);
}

inline bool SpaceCenter::CargoBay::open() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CargoBay_get_Open", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CargoBayState SpaceCenter::CargoBay::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CargoBay_get_State", _args);
  SpaceCenter::CargoBayState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::CargoBay::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "CargoBay_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::CargoBay::open_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "CargoBay_get_Open", _args));
}

inline ::krpc::Stream<SpaceCenter::CargoBayState> SpaceCenter::CargoBay::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CargoBayState>(this->_client, this->_client->request("SpaceCenter", "CargoBay_get_State", _args));
}

inline SpaceCenter::CelestialBody::CelestialBody(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::CelestialBody", id) {}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::angular_velocity(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_AngularVelocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::CelestialBody::bedrock_height(double latitude, double longitude) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_BedrockHeight", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::bedrock_position(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_BedrockPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::CelestialBody::biome_at(double latitude, double longitude) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_BiomeAt", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_Direction", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::msl_position(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_MSLPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double, double> SpaceCenter::CelestialBody::rotation(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::CelestialBody::surface_height(double latitude, double longitude) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_SurfaceHeight", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::surface_position(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_SurfacePosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::CelestialBody::velocity(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_Velocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::CelestialBody::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::flying_high_altitude_threshold() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_FlyingHighAltitudeThreshold", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::CelestialBody::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::rotational_period() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_RotationalPeriod", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::equatorial_radius() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_EquatorialRadius", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::space_high_altitude_threshold() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_SpaceHighAltitudeThreshold", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::CelestialBody::non_rotating_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_NonRotatingReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Orbit SpaceCenter::CelestialBody::orbit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_Orbit", _args);
  SpaceCenter::Orbit _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::rotational_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_RotationalSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::surface_gravity() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_SurfaceGravity", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::gravitational_parameter() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_GravitationalParameter", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::set<std::string> SpaceCenter::CelestialBody::biomes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_Biomes", _args);
  std::set<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::CelestialBody> SpaceCenter::CelestialBody::satellites() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_Satellites", _args);
  std::vector<SpaceCenter::CelestialBody> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::CelestialBody::has_atmosphere() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_HasAtmosphere", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::CelestialBody::orbital_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_OrbitalReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::sphere_of_influence() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_SphereOfInfluence", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_Mass", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::CelestialBody::atmosphere_depth() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_AtmosphereDepth", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::CelestialBody::has_atmospheric_oxygen() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "CelestialBody_get_HasAtmosphericOxygen", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::angular_velocity_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_AngularVelocity", _args));
}

inline ::krpc::Stream<double> SpaceCenter::CelestialBody::bedrock_height_stream(double latitude, double longitude) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_BedrockHeight", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::bedrock_position_stream(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_BedrockPosition", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::CelestialBody::biome_at_stream(double latitude, double longitude) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_BiomeAt", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_Direction", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::msl_position_stream(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_MSLPosition", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_Position", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> SpaceCenter::CelestialBody::rotation_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_Rotation", _args));
}

inline ::krpc::Stream<double> SpaceCenter::CelestialBody::surface_height_stream(double latitude, double longitude) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_SurfaceHeight", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::surface_position_stream(double latitude, double longitude, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_SurfacePosition", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::CelestialBody::velocity_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_Velocity", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::CelestialBody::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::flying_high_altitude_threshold_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_FlyingHighAltitudeThreshold", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::CelestialBody::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_Name", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::rotational_period_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_RotationalPeriod", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::equatorial_radius_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_EquatorialRadius", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::space_high_altitude_threshold_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_SpaceHighAltitudeThreshold", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::CelestialBody::non_rotating_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_NonRotatingReferenceFrame", _args));
}

inline ::krpc::Stream<SpaceCenter::Orbit> SpaceCenter::CelestialBody::orbit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Orbit>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_Orbit", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::rotational_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_RotationalSpeed", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::surface_gravity_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_SurfaceGravity", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::gravitational_parameter_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_GravitationalParameter", _args));
}

inline ::krpc::Stream<std::set<std::string>> SpaceCenter::CelestialBody::biomes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::set<std::string>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_Biomes", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::CelestialBody>> SpaceCenter::CelestialBody::satellites_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::CelestialBody>>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_Satellites", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::CelestialBody::has_atmosphere_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_HasAtmosphere", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::CelestialBody::orbital_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_OrbitalReferenceFrame", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::sphere_of_influence_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_SphereOfInfluence", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_Mass", _args));
}

inline ::krpc::Stream<float> SpaceCenter::CelestialBody::atmosphere_depth_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_AtmosphereDepth", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::CelestialBody::has_atmospheric_oxygen_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "CelestialBody_get_HasAtmosphericOxygen", _args));
}

inline SpaceCenter::Control::Control(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Control", id) {}

inline std::vector<SpaceCenter::Vessel> SpaceCenter::Control::activate_next_stage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_ActivateNextStage", _args);
  std::vector<SpaceCenter::Vessel> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Node SpaceCenter::Control::add_node(double ut, float prograde = 0.0, float normal = 0.0, float radial = 0.0) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(ut));
  _args.push_back(encoder::encode(prograde));
  _args.push_back(encoder::encode(normal));
  _args.push_back(encoder::encode(radial));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_AddNode", _args);
  SpaceCenter::Node _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Control::get_action_group(google::protobuf::uint32 group) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(group));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_GetActionGroup", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::remove_nodes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Control_RemoveNodes", _args);
}

inline void SpaceCenter::Control::set_action_group(google::protobuf::uint32 group, bool state) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(group));
  _args.push_back(encoder::encode(state));
  this->_client->invoke("SpaceCenter", "Control_SetActionGroup", _args);
}

inline void SpaceCenter::Control::toggle_action_group(google::protobuf::uint32 group) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(group));
  this->_client->invoke("SpaceCenter", "Control_ToggleActionGroup", _args);
}

inline float SpaceCenter::Control::right() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Right", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Control::brakes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Brakes", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_yaw(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Yaw", _args);
}

inline void SpaceCenter::Control::set_up(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Up", _args);
}

inline float SpaceCenter::Control::up() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Up", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Control::abort() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Abort", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline google::protobuf::int32 SpaceCenter::Control::current_stage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_CurrentStage", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Control::pitch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Pitch", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Control::sas() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_SAS", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_brakes(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Brakes", _args);
}

inline void SpaceCenter::Control::set_right(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Right", _args);
}

inline float SpaceCenter::Control::yaw() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Yaw", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Control::rcs() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_RCS", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Control::lights() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Lights", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::SASMode SpaceCenter::Control::sas_mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_SASMode", _args);
  SpaceCenter::SASMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Control::forward() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Forward", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_gear(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Gear", _args);
}

inline float SpaceCenter::Control::roll() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Roll", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_sas(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_SAS", _args);
}

inline bool SpaceCenter::Control::gear() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Gear", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_wheel_throttle(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_WheelThrottle", _args);
}

inline float SpaceCenter::Control::wheel_steering() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_WheelSteering", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_wheel_steering(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_WheelSteering", _args);
}

inline void SpaceCenter::Control::set_speed_mode(SpaceCenter::SpeedMode value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_SpeedMode", _args);
}

inline void SpaceCenter::Control::set_throttle(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Throttle", _args);
}

inline std::vector<SpaceCenter::Node> SpaceCenter::Control::nodes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Nodes", _args);
  std::vector<SpaceCenter::Node> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_sas_mode(SpaceCenter::SASMode value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_SASMode", _args);
}

inline void SpaceCenter::Control::set_abort(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Abort", _args);
}

inline float SpaceCenter::Control::throttle() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_Throttle", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_pitch(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Pitch", _args);
}

inline void SpaceCenter::Control::set_forward(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Forward", _args);
}

inline float SpaceCenter::Control::wheel_throttle() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_WheelThrottle", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Control::set_lights(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Lights", _args);
}

inline void SpaceCenter::Control::set_roll(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_Roll", _args);
}

inline void SpaceCenter::Control::set_rcs(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Control_set_RCS", _args);
}

inline SpaceCenter::SpeedMode SpaceCenter::Control::speed_mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Control_get_SpeedMode", _args);
  SpaceCenter::SpeedMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::vector<SpaceCenter::Vessel>> SpaceCenter::Control::activate_next_stage_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Vessel>>(this->_client, this->_client->request("SpaceCenter", "Control_ActivateNextStage", _args));
}

inline ::krpc::Stream<SpaceCenter::Node> SpaceCenter::Control::add_node_stream(double ut, float prograde = 0.0, float normal = 0.0, float radial = 0.0) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(ut));
  _args.push_back(encoder::encode(prograde));
  _args.push_back(encoder::encode(normal));
  _args.push_back(encoder::encode(radial));
  return ::krpc::Stream<SpaceCenter::Node>(this->_client, this->_client->request("SpaceCenter", "Control_AddNode", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::get_action_group_stream(google::protobuf::uint32 group) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(group));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_GetActionGroup", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::right_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Right", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::brakes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_get_Brakes", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::up_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Up", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::abort_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_get_Abort", _args));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::Control::current_stage_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "Control_get_CurrentStage", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::pitch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Pitch", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::sas_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_get_SAS", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::yaw_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Yaw", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::rcs_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_get_RCS", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::lights_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_get_Lights", _args));
}

inline ::krpc::Stream<SpaceCenter::SASMode> SpaceCenter::Control::sas_mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::SASMode>(this->_client, this->_client->request("SpaceCenter", "Control_get_SASMode", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::forward_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Forward", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::roll_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Roll", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Control::gear_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Control_get_Gear", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::wheel_steering_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_WheelSteering", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Node>> SpaceCenter::Control::nodes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Node>>(this->_client, this->_client->request("SpaceCenter", "Control_get_Nodes", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::throttle_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_Throttle", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Control::wheel_throttle_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Control_get_WheelThrottle", _args));
}

inline ::krpc::Stream<SpaceCenter::SpeedMode> SpaceCenter::Control::speed_mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::SpeedMode>(this->_client, this->_client->request("SpaceCenter", "Control_get_SpeedMode", _args));
}

inline SpaceCenter::ControlSurface::ControlSurface(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ControlSurface", id) {}

inline void SpaceCenter::ControlSurface::set_roll_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ControlSurface_set_RollEnabled", _args);
}

inline void SpaceCenter::ControlSurface::set_deployed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ControlSurface_set_Deployed", _args);
}

inline bool SpaceCenter::ControlSurface::roll_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_RollEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::ControlSurface::set_inverted(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ControlSurface_set_Inverted", _args);
}

inline void SpaceCenter::ControlSurface::set_yaw_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ControlSurface_set_YawEnabled", _args);
}

inline bool SpaceCenter::ControlSurface::inverted() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_Inverted", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::ControlSurface::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::ControlSurface::set_pitch_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ControlSurface_set_PitchEnabled", _args);
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::ControlSurface::available_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_AvailableTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ControlSurface::surface_area() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_SurfaceArea", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ControlSurface::yaw_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_YawEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ControlSurface::pitch_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_PitchEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ControlSurface::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ControlSurface_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> SpaceCenter::ControlSurface::roll_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_RollEnabled", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ControlSurface::inverted_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_Inverted", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::ControlSurface::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_Part", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::ControlSurface::available_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_AvailableTorque", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ControlSurface::surface_area_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_SurfaceArea", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ControlSurface::yaw_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_YawEnabled", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ControlSurface::pitch_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_PitchEnabled", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ControlSurface::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ControlSurface_get_Deployed", _args));
}

inline SpaceCenter::Decoupler::Decoupler(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Decoupler", id) {}

inline SpaceCenter::Vessel SpaceCenter::Decoupler::decouple() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Decoupler_Decouple", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Decoupler::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Decoupler_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Decoupler::staged() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Decoupler_get_Staged", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Decoupler::impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Decoupler_get_Impulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Decoupler::decoupled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Decoupler_get_Decoupled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::Vessel> SpaceCenter::Decoupler::decouple_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("SpaceCenter", "Decoupler_Decouple", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Decoupler::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Decoupler_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Decoupler::staged_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Decoupler_get_Staged", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Decoupler::impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Decoupler_get_Impulse", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Decoupler::decoupled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Decoupler_get_Decoupled", _args));
}

inline SpaceCenter::DockingPort::DockingPort(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::DockingPort", id) {}

inline std::tuple<double, double, double> SpaceCenter::DockingPort::direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_Direction", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::DockingPort::position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double, double> SpaceCenter::DockingPort::rotation(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel SpaceCenter::DockingPort::undock() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_Undock", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::DockingPort::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::DockingPort::shielded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_Shielded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::DockingPort::reengage_distance() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_ReengageDistance", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::DockingPort::has_shield() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_HasShield", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::DockingPort::set_shielded(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "DockingPort_set_Shielded", _args);
}

inline SpaceCenter::Part SpaceCenter::DockingPort::docked_part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_DockedPart", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::DockingPortState SpaceCenter::DockingPort::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_State", _args);
  SpaceCenter::DockingPortState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::DockingPort::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "DockingPort_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::DockingPort::direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "DockingPort_Direction", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::DockingPort::position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "DockingPort_Position", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> SpaceCenter::DockingPort::rotation_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("SpaceCenter", "DockingPort_Rotation", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> SpaceCenter::DockingPort::undock_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("SpaceCenter", "DockingPort_Undock", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::DockingPort::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::DockingPort::shielded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_Shielded", _args));
}

inline ::krpc::Stream<float> SpaceCenter::DockingPort::reengage_distance_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_ReengageDistance", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::DockingPort::has_shield_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_HasShield", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::DockingPort::docked_part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_DockedPart", _args));
}

inline ::krpc::Stream<SpaceCenter::DockingPortState> SpaceCenter::DockingPort::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::DockingPortState>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::DockingPort::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "DockingPort_get_Part", _args));
}

inline SpaceCenter::Engine::Engine(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Engine", id) {}

inline void SpaceCenter::Engine::toggle_mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Engine_ToggleMode", _args);
}

inline bool SpaceCenter::Engine::has_modes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_HasModes", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::gimbal_locked() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_GimbalLocked", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Thrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Engine::set_auto_mode_switch(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Engine_set_AutoModeSwitch", _args);
}

inline bool SpaceCenter::Engine::has_fuel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_HasFuel", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_SpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Engine::set_mode(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Engine_set_Mode", _args);
}

inline float SpaceCenter::Engine::available_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_AvailableThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::thrust_limit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_ThrustLimit", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::can_shutdown() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_CanShutdown", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::throttle_locked() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_ThrottleLocked", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Engine::set_gimbal_limit(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Engine_set_GimbalLimit", _args);
}

inline void SpaceCenter::Engine::set_thrust_limit(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Engine_set_ThrustLimit", _args);
}

inline float SpaceCenter::Engine::max_vacuum_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_MaxVacuumThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::gimbal_range() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_GimbalRange", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::Engine::propellant_names() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_PropellantNames", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::can_restart() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_CanRestart", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Engine::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Thruster> SpaceCenter::Engine::thrusters() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Thrusters", _args);
  std::vector<SpaceCenter::Thruster> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Propellant> SpaceCenter::Engine::propellants() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Propellants", _args);
  std::vector<SpaceCenter::Propellant> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Engine::available_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_AvailableTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::throttle() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Throttle", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::map<std::string, SpaceCenter::Engine> SpaceCenter::Engine::modes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Modes", _args);
  std::map<std::string, SpaceCenter::Engine> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Engine::set_active(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Engine_set_Active", _args);
}

inline float SpaceCenter::Engine::kerbin_sea_level_specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_KerbinSeaLevelSpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::map<std::string, float> SpaceCenter::Engine::propellant_ratios() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_PropellantRatios", _args);
  std::map<std::string, float> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::auto_mode_switch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_AutoModeSwitch", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Engine::mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Mode", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::vacuum_specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_VacuumSpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::max_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_MaxThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Engine::gimballed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_Gimballed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Engine::gimbal_limit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Engine_get_GimbalLimit", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Engine::set_gimbal_locked(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Engine_set_GimbalLocked", _args);
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::has_modes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_HasModes", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::gimbal_locked_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_GimbalLocked", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Thrust", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::has_fuel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_HasFuel", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_SpecificImpulse", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::available_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_AvailableThrust", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::thrust_limit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_ThrustLimit", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::can_shutdown_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_CanShutdown", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::throttle_locked_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_ThrottleLocked", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::max_vacuum_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_MaxVacuumThrust", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::gimbal_range_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_GimbalRange", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::Engine::propellant_names_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "Engine_get_PropellantNames", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::can_restart_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_CanRestart", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Engine::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Part", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Thruster>> SpaceCenter::Engine::thrusters_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Thruster>>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Thrusters", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Active", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Propellant>> SpaceCenter::Engine::propellants_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Propellant>>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Propellants", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Engine::available_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Engine_get_AvailableTorque", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::throttle_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Throttle", _args));
}

inline ::krpc::Stream<std::map<std::string, SpaceCenter::Engine>> SpaceCenter::Engine::modes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::map<std::string, SpaceCenter::Engine>>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Modes", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::kerbin_sea_level_specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_KerbinSeaLevelSpecificImpulse", _args));
}

inline ::krpc::Stream<std::map<std::string, float>> SpaceCenter::Engine::propellant_ratios_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::map<std::string, float>>(this->_client, this->_client->request("SpaceCenter", "Engine_get_PropellantRatios", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::auto_mode_switch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_AutoModeSwitch", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Engine::mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Mode", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::vacuum_specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_VacuumSpecificImpulse", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::max_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_MaxThrust", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Engine::gimballed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Engine_get_Gimballed", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Engine::gimbal_limit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Engine_get_GimbalLimit", _args));
}

inline SpaceCenter::Experiment::Experiment(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Experiment", id) {}

inline void SpaceCenter::Experiment::dump() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Experiment_Dump", _args);
}

inline void SpaceCenter::Experiment::reset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Experiment_Reset", _args);
}

inline void SpaceCenter::Experiment::run() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Experiment_Run", _args);
}

inline void SpaceCenter::Experiment::transmit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Experiment_Transmit", _args);
}

inline bool SpaceCenter::Experiment::available() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Available", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Experiment::biome() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Biome", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ScienceSubject SpaceCenter::Experiment::science_subject() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_ScienceSubject", _args);
  SpaceCenter::ScienceSubject _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Experiment::inoperable() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Inoperable", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Experiment::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Experiment::rerunnable() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Rerunnable", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::ScienceData> SpaceCenter::Experiment::data() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Data", _args);
  std::vector<SpaceCenter::ScienceData> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Experiment::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Experiment::has_data() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Experiment_get_HasData", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> SpaceCenter::Experiment::available_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Available", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Experiment::biome_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Biome", _args));
}

inline ::krpc::Stream<SpaceCenter::ScienceSubject> SpaceCenter::Experiment::science_subject_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ScienceSubject>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_ScienceSubject", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Experiment::inoperable_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Inoperable", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Experiment::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Experiment::rerunnable_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Rerunnable", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::ScienceData>> SpaceCenter::Experiment::data_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::ScienceData>>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Data", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Experiment::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_Deployed", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Experiment::has_data_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Experiment_get_HasData", _args));
}

inline SpaceCenter::Fairing::Fairing(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Fairing", id) {}

inline void SpaceCenter::Fairing::jettison() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Fairing_Jettison", _args);
}

inline SpaceCenter::Part SpaceCenter::Fairing::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Fairing_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Fairing::jettisoned() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Fairing_get_Jettisoned", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Fairing::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Fairing_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Fairing::jettisoned_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Fairing_get_Jettisoned", _args));
}

inline SpaceCenter::Flight::Flight(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Flight", id) {}

inline float SpaceCenter::Flight::g_force() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_GForce", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::reynolds_number() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_ReynoldsNumber", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::true_air_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_TrueAirSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::static_pressure_at_msl() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_StaticPressureAtMSL", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::ballistic_coefficient() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_BallisticCoefficient", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::pitch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Pitch", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::prograde() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Prograde", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Speed", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::drag_coefficient() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_DragCoefficient", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::sideslip_angle() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_SideslipAngle", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::mean_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_MeanAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::speed_of_sound() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_SpeedOfSound", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::velocity() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Velocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::total_air_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_TotalAirTemperature", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::anti_normal() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_AntiNormal", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::surface_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_SurfaceAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::latitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Latitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::center_of_mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_CenterOfMass", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::atmosphere_density() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_AtmosphereDensity", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::equivalent_air_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_EquivalentAirSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::bedrock_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_BedrockAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::vertical_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_VerticalSpeed", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::angle_of_attack() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_AngleOfAttack", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::direction() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Direction", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::elevation() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Elevation", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::normal() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Normal", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::horizontal_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_HorizontalSpeed", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::retrograde() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Retrograde", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::drag() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Drag", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::lift() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Lift", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::stall_fraction() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_StallFraction", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::terminal_velocity() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_TerminalVelocity", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::lift_coefficient() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_LiftCoefficient", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double, double> SpaceCenter::Flight::rotation() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::thrust_specific_fuel_consumption() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_ThrustSpecificFuelConsumption", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::mach() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Mach", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::dynamic_pressure() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_DynamicPressure", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Flight::longitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Longitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::roll() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Roll", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::aerodynamic_force() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_AerodynamicForce", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::radial() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Radial", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Flight::anti_radial() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_AntiRadial", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::static_air_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_StaticAirTemperature", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::heading() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_Heading", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Flight::static_pressure() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Flight_get_StaticPressure", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::Flight::g_force_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_GForce", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::reynolds_number_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_ReynoldsNumber", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::true_air_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_TrueAirSpeed", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::static_pressure_at_msl_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_StaticPressureAtMSL", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::ballistic_coefficient_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_BallisticCoefficient", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::pitch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Pitch", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::prograde_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Prograde", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Speed", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::drag_coefficient_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_DragCoefficient", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::sideslip_angle_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_SideslipAngle", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::mean_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_MeanAltitude", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::speed_of_sound_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_SpeedOfSound", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::velocity_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Velocity", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::total_air_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_TotalAirTemperature", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::anti_normal_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_AntiNormal", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::surface_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_SurfaceAltitude", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::latitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Latitude", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::center_of_mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_CenterOfMass", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::atmosphere_density_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_AtmosphereDensity", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::equivalent_air_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_EquivalentAirSpeed", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::bedrock_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_BedrockAltitude", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::vertical_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_VerticalSpeed", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::angle_of_attack_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_AngleOfAttack", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::direction_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Direction", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::elevation_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Elevation", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::normal_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Normal", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::horizontal_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_HorizontalSpeed", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::retrograde_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Retrograde", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::drag_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Drag", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::lift_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Lift", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::stall_fraction_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_StallFraction", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::terminal_velocity_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_TerminalVelocity", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::lift_coefficient_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_LiftCoefficient", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> SpaceCenter::Flight::rotation_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Rotation", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::thrust_specific_fuel_consumption_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_ThrustSpecificFuelConsumption", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::mach_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Mach", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::dynamic_pressure_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_DynamicPressure", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Flight::longitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Longitude", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::roll_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Roll", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::aerodynamic_force_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_AerodynamicForce", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::radial_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Radial", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Flight::anti_radial_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Flight_get_AntiRadial", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::static_air_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_StaticAirTemperature", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::heading_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_Heading", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Flight::static_pressure_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Flight_get_StaticPressure", _args));
}

inline SpaceCenter::Force::Force(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Force", id) {}

inline void SpaceCenter::Force::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Force_Remove", _args);
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Force::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Force_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Force::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Force_set_ReferenceFrame", _args);
}

inline std::tuple<double, double, double> SpaceCenter::Force::force_vector() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Force_get_ForceVector", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Force::set_force_vector(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Force_set_ForceVector", _args);
}

inline SpaceCenter::Part SpaceCenter::Force::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Force_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Force::position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Force_get_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Force::set_position(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Force_set_Position", _args);
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Force::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Force_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Force::force_vector_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Force_get_ForceVector", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Force::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Force_get_Part", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Force::position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Force_get_Position", _args));
}

inline SpaceCenter::Intake::Intake(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Intake", id) {}

inline void SpaceCenter::Intake::set_open(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Intake_set_Open", _args);
}

inline float SpaceCenter::Intake::area() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Intake_get_Area", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Intake::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Intake_get_Speed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Intake::flow() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Intake_get_Flow", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Intake::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Intake_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Intake::open() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Intake_get_Open", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::Intake::area_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Intake_get_Area", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Intake::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Intake_get_Speed", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Intake::flow_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Intake_get_Flow", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Intake::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Intake_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Intake::open_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Intake_get_Open", _args));
}

inline SpaceCenter::LandingGear::LandingGear(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::LandingGear", id) {}

inline void SpaceCenter::LandingGear::set_deployed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "LandingGear_set_Deployed", _args);
}

inline bool SpaceCenter::LandingGear::deployable() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingGear_get_Deployable", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::LandingGearState SpaceCenter::LandingGear::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingGear_get_State", _args);
  SpaceCenter::LandingGearState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::LandingGear::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingGear_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::LandingGear::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingGear_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::LandingGear::is_grounded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingGear_get_IsGrounded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> SpaceCenter::LandingGear::deployable_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "LandingGear_get_Deployable", _args));
}

inline ::krpc::Stream<SpaceCenter::LandingGearState> SpaceCenter::LandingGear::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::LandingGearState>(this->_client, this->_client->request("SpaceCenter", "LandingGear_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::LandingGear::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "LandingGear_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::LandingGear::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "LandingGear_get_Deployed", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::LandingGear::is_grounded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "LandingGear_get_IsGrounded", _args));
}

inline SpaceCenter::LandingLeg::LandingLeg(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::LandingLeg", id) {}

inline void SpaceCenter::LandingLeg::set_deployed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "LandingLeg_set_Deployed", _args);
}

inline SpaceCenter::LandingLegState SpaceCenter::LandingLeg::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingLeg_get_State", _args);
  SpaceCenter::LandingLegState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::LandingLeg::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingLeg_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::LandingLeg::is_grounded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingLeg_get_IsGrounded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::LandingLeg::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LandingLeg_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::LandingLegState> SpaceCenter::LandingLeg::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::LandingLegState>(this->_client, this->_client->request("SpaceCenter", "LandingLeg_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::LandingLeg::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "LandingLeg_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::LandingLeg::is_grounded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "LandingLeg_get_IsGrounded", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::LandingLeg::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "LandingLeg_get_Deployed", _args));
}

inline SpaceCenter::LaunchClamp::LaunchClamp(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::LaunchClamp", id) {}

inline void SpaceCenter::LaunchClamp::release() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "LaunchClamp_Release", _args);
}

inline SpaceCenter::Part SpaceCenter::LaunchClamp::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "LaunchClamp_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::LaunchClamp::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "LaunchClamp_get_Part", _args));
}

inline SpaceCenter::Light::Light(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Light", id) {}

inline float SpaceCenter::Light::power_usage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Light_get_PowerUsage", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Light::set_active(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Light_set_Active", _args);
}

inline std::tuple<float, float, float> SpaceCenter::Light::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Light_get_Color", _args);
  std::tuple<float, float, float> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Light::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Light_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Light::active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Light_get_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Light::set_color(std::tuple<float, float, float> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Light_set_Color", _args);
}

inline ::krpc::Stream<float> SpaceCenter::Light::power_usage_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Light_get_PowerUsage", _args));
}

inline ::krpc::Stream<std::tuple<float, float, float>> SpaceCenter::Light::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<float, float, float>>(this->_client, this->_client->request("SpaceCenter", "Light_get_Color", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Light::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Light_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Light::active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Light_get_Active", _args));
}

inline SpaceCenter::Module::Module(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Module", id) {}

inline std::string SpaceCenter::Module::get_field(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_GetField", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Module::has_action(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_HasAction", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Module::has_event(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_HasEvent", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Module::has_field(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_HasField", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Module::reset_field(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  this->_client->invoke("SpaceCenter", "Module_ResetField", _args);
}

inline void SpaceCenter::Module::set_action(std::string name, bool value = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Module_SetAction", _args);
}

inline void SpaceCenter::Module::set_field_float(std::string name, float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Module_SetFieldFloat", _args);
}

inline void SpaceCenter::Module::set_field_int(std::string name, google::protobuf::int32 value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Module_SetFieldInt", _args);
}

inline void SpaceCenter::Module::set_field_string(std::string name, std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Module_SetFieldString", _args);
}

inline void SpaceCenter::Module::trigger_event(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  this->_client->invoke("SpaceCenter", "Module_TriggerEvent", _args);
}

inline std::map<std::string, std::string> SpaceCenter::Module::fields() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_get_Fields", _args);
  std::map<std::string, std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Module::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::Module::events() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_get_Events", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::Module::actions() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_get_Actions", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Module::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Module_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::string> SpaceCenter::Module::get_field_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Module_GetField", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Module::has_action_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Module_HasAction", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Module::has_event_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Module_HasEvent", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Module::has_field_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Module_HasField", _args));
}

inline ::krpc::Stream<std::map<std::string, std::string>> SpaceCenter::Module::fields_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::map<std::string, std::string>>(this->_client, this->_client->request("SpaceCenter", "Module_get_Fields", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Module::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Module_get_Part", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::Module::events_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "Module_get_Events", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::Module::actions_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "Module_get_Actions", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Module::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Module_get_Name", _args));
}

inline SpaceCenter::Node::Node(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Node", id) {}

inline std::tuple<double, double, double> SpaceCenter::Node::burn_vector(SpaceCenter::ReferenceFrame reference_frame = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_BurnVector", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Node::direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_Direction", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Node::position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Node::remaining_burn_vector(SpaceCenter::ReferenceFrame reference_frame = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_RemainingBurnVector", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Node::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Node_Remove", _args);
}

inline double SpaceCenter::Node::remaining_delta_v() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_RemainingDeltaV", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Node::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Node::set_normal(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Node_set_Normal", _args);
}

inline double SpaceCenter::Node::normal() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_Normal", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Node::set_radial(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Node_set_Radial", _args);
}

inline double SpaceCenter::Node::ut() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_UT", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Node::delta_v() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_DeltaV", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Orbit SpaceCenter::Node::orbit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_Orbit", _args);
  SpaceCenter::Orbit _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Node::set_delta_v(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Node_set_DeltaV", _args);
}

inline void SpaceCenter::Node::set_prograde(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Node_set_Prograde", _args);
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Node::orbital_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_OrbitalReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Node::set_ut(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Node_set_UT", _args);
}

inline double SpaceCenter::Node::radial() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_Radial", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Node::prograde() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_Prograde", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Node::time_to() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Node_get_TimeTo", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Node::burn_vector_stream(SpaceCenter::ReferenceFrame reference_frame = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Node_BurnVector", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Node::direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Node_Direction", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Node::position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Node_Position", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Node::remaining_burn_vector_stream(SpaceCenter::ReferenceFrame reference_frame = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Node_RemainingBurnVector", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::remaining_delta_v_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_RemainingDeltaV", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Node::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Node_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::normal_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_Normal", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::ut_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_UT", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::delta_v_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_DeltaV", _args));
}

inline ::krpc::Stream<SpaceCenter::Orbit> SpaceCenter::Node::orbit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Orbit>(this->_client, this->_client->request("SpaceCenter", "Node_get_Orbit", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Node::orbital_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Node_get_OrbitalReferenceFrame", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::radial_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_Radial", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::prograde_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_Prograde", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Node::time_to_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Node_get_TimeTo", _args));
}

inline SpaceCenter::Orbit::Orbit(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Orbit", id) {}

inline double SpaceCenter::Orbit::eccentric_anomaly_at_ut(double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(ut));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_EccentricAnomalyAtUT", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::orbital_speed_at(double time) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(time));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_OrbitalSpeedAt", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::radius_at_true_anomaly(double true_anomaly) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(true_anomaly));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_RadiusAtTrueAnomaly", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::true_anomaly_at_radius(double radius) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(radius));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_TrueAnomalyAtRadius", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::true_anomaly_at_ut(double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(ut));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_TrueAnomalyAtUT", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::ut_at_true_anomaly(double true_anomaly) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(true_anomaly));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_UTAtTrueAnomaly", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::period() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Period", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::eccentric_anomaly() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_EccentricAnomaly", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::time_to_soi_change() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_TimeToSOIChange", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::apoapsis_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_ApoapsisAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Speed", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::orbital_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_OrbitalSpeed", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::time_to_apoapsis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_TimeToApoapsis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Orbit SpaceCenter::Orbit::next_orbit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_NextOrbit", _args);
  SpaceCenter::Orbit _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::periapsis_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_PeriapsisAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::mean_anomaly_at_epoch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_MeanAnomalyAtEpoch", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::mean_anomaly() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_MeanAnomaly", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::epoch() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Epoch", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::argument_of_periapsis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_ArgumentOfPeriapsis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::inclination() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Inclination", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CelestialBody SpaceCenter::Orbit::body() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Body", _args);
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::eccentricity() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Eccentricity", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::periapsis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Periapsis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::semi_major_axis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_SemiMajorAxis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::time_to_periapsis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_TimeToPeriapsis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::longitude_of_ascending_node() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_LongitudeOfAscendingNode", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::semi_minor_axis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_SemiMinorAxis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::apoapsis() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Apoapsis", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::radius() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_Radius", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Orbit::true_anomaly() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Orbit_get_TrueAnomaly", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Orbit::reference_plane_direction(Client& _client, SpaceCenter::ReferenceFrame reference_frame) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = _client.invoke("SpaceCenter", "Orbit_ReferencePlaneDirection", _args);
    std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Orbit::reference_plane_normal(Client& _client, SpaceCenter::ReferenceFrame reference_frame) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = _client.invoke("SpaceCenter", "Orbit_ReferencePlaneNormal", _args);
    std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::eccentric_anomaly_at_ut_stream(double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(ut));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_EccentricAnomalyAtUT", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::orbital_speed_at_stream(double time) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(time));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_OrbitalSpeedAt", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::radius_at_true_anomaly_stream(double true_anomaly) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(true_anomaly));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_RadiusAtTrueAnomaly", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::true_anomaly_at_radius_stream(double radius) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(radius));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_TrueAnomalyAtRadius", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::true_anomaly_at_ut_stream(double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(ut));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_TrueAnomalyAtUT", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::ut_at_true_anomaly_stream(double true_anomaly) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(true_anomaly));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_UTAtTrueAnomaly", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::period_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Period", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::eccentric_anomaly_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_EccentricAnomaly", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::time_to_soi_change_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_TimeToSOIChange", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::apoapsis_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_ApoapsisAltitude", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Speed", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::orbital_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_OrbitalSpeed", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::time_to_apoapsis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_TimeToApoapsis", _args));
}

inline ::krpc::Stream<SpaceCenter::Orbit> SpaceCenter::Orbit::next_orbit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Orbit>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_NextOrbit", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::periapsis_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_PeriapsisAltitude", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::mean_anomaly_at_epoch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_MeanAnomalyAtEpoch", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::mean_anomaly_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_MeanAnomaly", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::epoch_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Epoch", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::argument_of_periapsis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_ArgumentOfPeriapsis", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::inclination_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Inclination", _args));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> SpaceCenter::Orbit::body_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Body", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::eccentricity_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Eccentricity", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::periapsis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Periapsis", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::semi_major_axis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_SemiMajorAxis", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::time_to_periapsis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_TimeToPeriapsis", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::longitude_of_ascending_node_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_LongitudeOfAscendingNode", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::semi_minor_axis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_SemiMinorAxis", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::apoapsis_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Apoapsis", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::radius_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_Radius", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Orbit::true_anomaly_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Orbit_get_TrueAnomaly", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Orbit::reference_plane_direction_stream(Client& _client, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(&_client, _client.request("SpaceCenter", "Orbit_ReferencePlaneDirection", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Orbit::reference_plane_normal_stream(Client& _client, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(&_client, _client.request("SpaceCenter", "Orbit_ReferencePlaneNormal", _args));
}

inline SpaceCenter::Parachute::Parachute(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Parachute", id) {}

inline void SpaceCenter::Parachute::deploy() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Parachute_Deploy", _args);
}

inline float SpaceCenter::Parachute::deploy_min_pressure() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parachute_get_DeployMinPressure", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Parachute::set_deploy_altitude(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Parachute_set_DeployAltitude", _args);
}

inline float SpaceCenter::Parachute::deploy_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parachute_get_DeployAltitude", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ParachuteState SpaceCenter::Parachute::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parachute_get_State", _args);
  SpaceCenter::ParachuteState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Parachute::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parachute_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Parachute::set_deploy_min_pressure(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Parachute_set_DeployMinPressure", _args);
}

inline bool SpaceCenter::Parachute::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parachute_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::Parachute::deploy_min_pressure_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Parachute_get_DeployMinPressure", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Parachute::deploy_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Parachute_get_DeployAltitude", _args));
}

inline ::krpc::Stream<SpaceCenter::ParachuteState> SpaceCenter::Parachute::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ParachuteState>(this->_client, this->_client->request("SpaceCenter", "Parachute_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Parachute::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Parachute_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Parachute::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Parachute_get_Deployed", _args));
}

inline SpaceCenter::Part::Part(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Part", id) {}

inline SpaceCenter::Force SpaceCenter::Part::add_force(std::tuple<double, double, double> force, std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(force));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_AddForce", _args);
  SpaceCenter::Force _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Part::bounding_box(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_BoundingBox", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Part::center_of_mass(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_CenterOfMass", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Part::direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_Direction", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Part::instantaneous_force(std::tuple<double, double, double> force, std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(force));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(reference_frame));
  this->_client->invoke("SpaceCenter", "Part_InstantaneousForce", _args);
}

inline std::tuple<double, double, double> SpaceCenter::Part::position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double, double> SpaceCenter::Part::rotation(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Part::velocity(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_Velocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Engine SpaceCenter::Part::engine() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Engine", _args);
  SpaceCenter::Engine _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Part::set_highlighted(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Part_set_Highlighted", _args);
}

inline double SpaceCenter::Part::temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Temperature", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Part::fuel_lines_from() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_FuelLinesFrom", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Fairing SpaceCenter::Part::fairing() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Fairing", _args);
  SpaceCenter::Fairing _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::max_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_MaxTemperature", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_skin_mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalSkinMass", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Part::tag() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Tag", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_conduction_flux() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalConductionFlux", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReactionWheel SpaceCenter::Part::reaction_wheel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ReactionWheel", _args);
  SpaceCenter::ReactionWheel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Parachute SpaceCenter::Part::parachute() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Parachute", _args);
  SpaceCenter::Parachute _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel SpaceCenter::Part::vessel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Vessel", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::cost() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Cost", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Part::parent() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Parent", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::LaunchClamp SpaceCenter::Part::launch_clamp() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_LaunchClamp", _args);
  SpaceCenter::LaunchClamp _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_convection_flux() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalConvectionFlux", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ResourceConverter SpaceCenter::Part::resource_converter() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ResourceConverter", _args);
  SpaceCenter::ResourceConverter _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::LandingGear SpaceCenter::Part::landing_gear() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_LandingGear", _args);
  SpaceCenter::LandingGear _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalMass", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Part::children() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Children", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Radiator SpaceCenter::Part::radiator() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Radiator", _args);
  SpaceCenter::Radiator _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<double> SpaceCenter::Part::inertia_tensor() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_InertiaTensor", _args);
  std::vector<double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_resource_mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalResourceMass", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::LandingLeg SpaceCenter::Part::landing_leg() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_LandingLeg", _args);
  SpaceCenter::LandingLeg _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::crossfeed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Crossfeed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Part::title() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Title", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::RCS SpaceCenter::Part::rcs() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_RCS", _args);
  SpaceCenter::RCS _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::highlighted() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Highlighted", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::impact_tolerance() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ImpactTolerance", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Experiment SpaceCenter::Part::experiment() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Experiment", _args);
  SpaceCenter::Experiment _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Part::center_of_mass_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_CenterOfMassReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline google::protobuf::int32 SpaceCenter::Part::decouple_stage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_DecoupleStage", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::massless() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Massless", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Sensor SpaceCenter::Part::sensor() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Sensor", _args);
  SpaceCenter::Sensor _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Resources SpaceCenter::Part::resources() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Resources", _args);
  SpaceCenter::Resources _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CargoBay SpaceCenter::Part::cargo_bay() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_CargoBay", _args);
  SpaceCenter::CargoBay _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Part::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Part::moment_of_inertia() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_MomentOfInertia", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::skin_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_SkinTemperature", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::radially_attached() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_RadiallyAttached", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ResourceHarvester SpaceCenter::Part::resource_harvester() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ResourceHarvester", _args);
  SpaceCenter::ResourceHarvester _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_radiation_flux() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalRadiationFlux", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::is_fuel_line() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_IsFuelLine", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_skin_to_internal_flux() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalSkinToInternalFlux", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Part::set_highlight_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Part_set_HighlightColor", _args);
}

inline google::protobuf::int32 SpaceCenter::Part::stage() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Stage", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Part::fuel_lines_to() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_FuelLinesTo", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Intake SpaceCenter::Part::intake() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Intake", _args);
  SpaceCenter::Intake _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Part::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::dynamic_pressure() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_DynamicPressure", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Decoupler SpaceCenter::Part::decoupler() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Decoupler", _args);
  SpaceCenter::Decoupler _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Light SpaceCenter::Part::light() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Light", _args);
  SpaceCenter::Light _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Part::thermal_internal_flux() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ThermalInternalFlux", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Module> SpaceCenter::Part::modules() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Modules", _args);
  std::vector<SpaceCenter::Module> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::axially_attached() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_AxiallyAttached", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Part::set_tag(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Part_set_Tag", _args);
}

inline std::tuple<double, double, double> SpaceCenter::Part::highlight_color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_HighlightColor", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ControlSurface SpaceCenter::Part::control_surface() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_ControlSurface", _args);
  SpaceCenter::ControlSurface _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Part::shielded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Shielded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::DockingPort SpaceCenter::Part::docking_port() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_DockingPort", _args);
  SpaceCenter::DockingPort _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_Mass", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::max_skin_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_MaxSkinTemperature", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::SolarPanel SpaceCenter::Part::solar_panel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_SolarPanel", _args);
  SpaceCenter::SolarPanel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Part::dry_mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Part_get_DryMass", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::Force> SpaceCenter::Part::add_force_stream(std::tuple<double, double, double> force, std::tuple<double, double, double> position, SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(force));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<SpaceCenter::Force>(this->_client, this->_client->request("SpaceCenter", "Part_AddForce", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Part::bounding_box_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Part_BoundingBox", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Part::center_of_mass_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_CenterOfMass", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Part::direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_Direction", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Part::position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_Position", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> SpaceCenter::Part::rotation_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_Rotation", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Part::velocity_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_Velocity", _args));
}

inline ::krpc::Stream<SpaceCenter::Engine> SpaceCenter::Part::engine_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Engine>(this->_client, this->_client->request("SpaceCenter", "Part_get_Engine", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_Temperature", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Part::fuel_lines_from_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Part_get_FuelLinesFrom", _args));
}

inline ::krpc::Stream<SpaceCenter::Fairing> SpaceCenter::Part::fairing_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Fairing>(this->_client, this->_client->request("SpaceCenter", "Part_get_Fairing", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::max_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_MaxTemperature", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_skin_mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalSkinMass", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Part::tag_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Part_get_Tag", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_conduction_flux_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalConductionFlux", _args));
}

inline ::krpc::Stream<SpaceCenter::ReactionWheel> SpaceCenter::Part::reaction_wheel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReactionWheel>(this->_client, this->_client->request("SpaceCenter", "Part_get_ReactionWheel", _args));
}

inline ::krpc::Stream<SpaceCenter::Parachute> SpaceCenter::Part::parachute_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Parachute>(this->_client, this->_client->request("SpaceCenter", "Part_get_Parachute", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> SpaceCenter::Part::vessel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->request("SpaceCenter", "Part_get_Vessel", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::cost_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_Cost", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Part::parent_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Part_get_Parent", _args));
}

inline ::krpc::Stream<SpaceCenter::LaunchClamp> SpaceCenter::Part::launch_clamp_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::LaunchClamp>(this->_client, this->_client->request("SpaceCenter", "Part_get_LaunchClamp", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_convection_flux_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalConvectionFlux", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceConverter> SpaceCenter::Part::resource_converter_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ResourceConverter>(this->_client, this->_client->request("SpaceCenter", "Part_get_ResourceConverter", _args));
}

inline ::krpc::Stream<SpaceCenter::LandingGear> SpaceCenter::Part::landing_gear_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::LandingGear>(this->_client, this->_client->request("SpaceCenter", "Part_get_LandingGear", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalMass", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Part::children_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Part_get_Children", _args));
}

inline ::krpc::Stream<SpaceCenter::Radiator> SpaceCenter::Part::radiator_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Radiator>(this->_client, this->_client->request("SpaceCenter", "Part_get_Radiator", _args));
}

inline ::krpc::Stream<std::vector<double>> SpaceCenter::Part::inertia_tensor_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<double>>(this->_client, this->_client->request("SpaceCenter", "Part_get_InertiaTensor", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_resource_mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalResourceMass", _args));
}

inline ::krpc::Stream<SpaceCenter::LandingLeg> SpaceCenter::Part::landing_leg_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::LandingLeg>(this->_client, this->_client->request("SpaceCenter", "Part_get_LandingLeg", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::crossfeed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_Crossfeed", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Part::title_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Part_get_Title", _args));
}

inline ::krpc::Stream<SpaceCenter::RCS> SpaceCenter::Part::rcs_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::RCS>(this->_client, this->_client->request("SpaceCenter", "Part_get_RCS", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::highlighted_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_Highlighted", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::impact_tolerance_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_ImpactTolerance", _args));
}

inline ::krpc::Stream<SpaceCenter::Experiment> SpaceCenter::Part::experiment_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Experiment>(this->_client, this->_client->request("SpaceCenter", "Part_get_Experiment", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Part::center_of_mass_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Part_get_CenterOfMassReferenceFrame", _args));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::Part::decouple_stage_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "Part_get_DecoupleStage", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::massless_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_Massless", _args));
}

inline ::krpc::Stream<SpaceCenter::Sensor> SpaceCenter::Part::sensor_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Sensor>(this->_client, this->_client->request("SpaceCenter", "Part_get_Sensor", _args));
}

inline ::krpc::Stream<SpaceCenter::Resources> SpaceCenter::Part::resources_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Resources>(this->_client, this->_client->request("SpaceCenter", "Part_get_Resources", _args));
}

inline ::krpc::Stream<SpaceCenter::CargoBay> SpaceCenter::Part::cargo_bay_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CargoBay>(this->_client, this->_client->request("SpaceCenter", "Part_get_CargoBay", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Part::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Part_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Part::moment_of_inertia_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_get_MomentOfInertia", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::skin_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_SkinTemperature", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::radially_attached_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_RadiallyAttached", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceHarvester> SpaceCenter::Part::resource_harvester_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ResourceHarvester>(this->_client, this->_client->request("SpaceCenter", "Part_get_ResourceHarvester", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_radiation_flux_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalRadiationFlux", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::is_fuel_line_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_IsFuelLine", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_skin_to_internal_flux_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalSkinToInternalFlux", _args));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::Part::stage_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "Part_get_Stage", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Part::fuel_lines_to_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Part_get_FuelLinesTo", _args));
}

inline ::krpc::Stream<SpaceCenter::Intake> SpaceCenter::Part::intake_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Intake>(this->_client, this->_client->request("SpaceCenter", "Part_get_Intake", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Part::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Part_get_Name", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::dynamic_pressure_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_DynamicPressure", _args));
}

inline ::krpc::Stream<SpaceCenter::Decoupler> SpaceCenter::Part::decoupler_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Decoupler>(this->_client, this->_client->request("SpaceCenter", "Part_get_Decoupler", _args));
}

inline ::krpc::Stream<SpaceCenter::Light> SpaceCenter::Part::light_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Light>(this->_client, this->_client->request("SpaceCenter", "Part_get_Light", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Part::thermal_internal_flux_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Part_get_ThermalInternalFlux", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Module>> SpaceCenter::Part::modules_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Module>>(this->_client, this->_client->request("SpaceCenter", "Part_get_Modules", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::axially_attached_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_AxiallyAttached", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Part::highlight_color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Part_get_HighlightColor", _args));
}

inline ::krpc::Stream<SpaceCenter::ControlSurface> SpaceCenter::Part::control_surface_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ControlSurface>(this->_client, this->_client->request("SpaceCenter", "Part_get_ControlSurface", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Part::shielded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Part_get_Shielded", _args));
}

inline ::krpc::Stream<SpaceCenter::DockingPort> SpaceCenter::Part::docking_port_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::DockingPort>(this->_client, this->_client->request("SpaceCenter", "Part_get_DockingPort", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_Mass", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::max_skin_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_MaxSkinTemperature", _args));
}

inline ::krpc::Stream<SpaceCenter::SolarPanel> SpaceCenter::Part::solar_panel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::SolarPanel>(this->_client, this->_client->request("SpaceCenter", "Part_get_SolarPanel", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Part::dry_mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Part_get_DryMass", _args));
}

inline SpaceCenter::Parts::Parts(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Parts", id) {}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::in_decouple_stage(google::protobuf::int32 stage) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(stage));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_InDecoupleStage", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::in_stage(google::protobuf::int32 stage) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(stage));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_InStage", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Module> SpaceCenter::Parts::modules_with_name(std::string module_name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(module_name));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_ModulesWithName", _args);
  std::vector<SpaceCenter::Module> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::with_module(std::string module_name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(module_name));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_WithModule", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::with_name(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_WithName", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::with_tag(std::string tag) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(tag));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_WithTag", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::with_title(std::string title) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(title));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_WithTitle", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Part> SpaceCenter::Parts::all() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_All", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::LandingLeg> SpaceCenter::Parts::landing_legs() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_LandingLegs", _args);
  std::vector<SpaceCenter::LandingLeg> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Radiator> SpaceCenter::Parts::radiators() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Radiators", _args);
  std::vector<SpaceCenter::Radiator> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Experiment> SpaceCenter::Parts::experiments() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Experiments", _args);
  std::vector<SpaceCenter::Experiment> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::LandingGear> SpaceCenter::Parts::landing_gear() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_LandingGear", _args);
  std::vector<SpaceCenter::LandingGear> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Decoupler> SpaceCenter::Parts::decouplers() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Decouplers", _args);
  std::vector<SpaceCenter::Decoupler> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::SolarPanel> SpaceCenter::Parts::solar_panels() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_SolarPanels", _args);
  std::vector<SpaceCenter::SolarPanel> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::ResourceConverter> SpaceCenter::Parts::resource_converters() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_ResourceConverters", _args);
  std::vector<SpaceCenter::ResourceConverter> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Engine> SpaceCenter::Parts::engines() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Engines", _args);
  std::vector<SpaceCenter::Engine> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::RCS> SpaceCenter::Parts::rcs() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_RCS", _args);
  std::vector<SpaceCenter::RCS> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Light> SpaceCenter::Parts::lights() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Lights", _args);
  std::vector<SpaceCenter::Light> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::ReactionWheel> SpaceCenter::Parts::reaction_wheels() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_ReactionWheels", _args);
  std::vector<SpaceCenter::ReactionWheel> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Parts::set_controlling(SpaceCenter::Part value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Parts_set_Controlling", _args);
}

inline std::vector<SpaceCenter::Fairing> SpaceCenter::Parts::fairings() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Fairings", _args);
  std::vector<SpaceCenter::Fairing> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Parts::controlling() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Controlling", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Intake> SpaceCenter::Parts::intakes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Intakes", _args);
  std::vector<SpaceCenter::Intake> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Sensor> SpaceCenter::Parts::sensors() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Sensors", _args);
  std::vector<SpaceCenter::Sensor> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::ControlSurface> SpaceCenter::Parts::control_surfaces() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_ControlSurfaces", _args);
  std::vector<SpaceCenter::ControlSurface> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::CargoBay> SpaceCenter::Parts::cargo_bays() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_CargoBays", _args);
  std::vector<SpaceCenter::CargoBay> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::DockingPort> SpaceCenter::Parts::docking_ports() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_DockingPorts", _args);
  std::vector<SpaceCenter::DockingPort> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::ResourceHarvester> SpaceCenter::Parts::resource_harvesters() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_ResourceHarvesters", _args);
  std::vector<SpaceCenter::ResourceHarvester> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Parachute> SpaceCenter::Parts::parachutes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Parachutes", _args);
  std::vector<SpaceCenter::Parachute> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::LaunchClamp> SpaceCenter::Parts::launch_clamps() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_LaunchClamps", _args);
  std::vector<SpaceCenter::LaunchClamp> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Parts::root() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Parts_get_Root", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::in_decouple_stage_stream(google::protobuf::int32 stage) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(stage));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_InDecoupleStage", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::in_stage_stream(google::protobuf::int32 stage) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(stage));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_InStage", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Module>> SpaceCenter::Parts::modules_with_name_stream(std::string module_name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(module_name));
  return ::krpc::Stream<std::vector<SpaceCenter::Module>>(this->_client, this->_client->request("SpaceCenter", "Parts_ModulesWithName", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::with_module_stream(std::string module_name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(module_name));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_WithModule", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::with_name_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_WithName", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::with_tag_stream(std::string tag) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(tag));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_WithTag", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::with_title_stream(std::string title) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(title));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_WithTitle", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> SpaceCenter::Parts::all_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_All", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::LandingLeg>> SpaceCenter::Parts::landing_legs_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::LandingLeg>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_LandingLegs", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Radiator>> SpaceCenter::Parts::radiators_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Radiator>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Radiators", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Experiment>> SpaceCenter::Parts::experiments_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Experiment>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Experiments", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::LandingGear>> SpaceCenter::Parts::landing_gear_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::LandingGear>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_LandingGear", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Decoupler>> SpaceCenter::Parts::decouplers_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Decoupler>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Decouplers", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::SolarPanel>> SpaceCenter::Parts::solar_panels_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::SolarPanel>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_SolarPanels", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::ResourceConverter>> SpaceCenter::Parts::resource_converters_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::ResourceConverter>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_ResourceConverters", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Engine>> SpaceCenter::Parts::engines_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Engine>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Engines", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::RCS>> SpaceCenter::Parts::rcs_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::RCS>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_RCS", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Light>> SpaceCenter::Parts::lights_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Light>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Lights", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::ReactionWheel>> SpaceCenter::Parts::reaction_wheels_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::ReactionWheel>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_ReactionWheels", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Fairing>> SpaceCenter::Parts::fairings_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Fairing>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Fairings", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Parts::controlling_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Controlling", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Intake>> SpaceCenter::Parts::intakes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Intake>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Intakes", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Sensor>> SpaceCenter::Parts::sensors_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Sensor>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Sensors", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::ControlSurface>> SpaceCenter::Parts::control_surfaces_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::ControlSurface>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_ControlSurfaces", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::CargoBay>> SpaceCenter::Parts::cargo_bays_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::CargoBay>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_CargoBays", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::DockingPort>> SpaceCenter::Parts::docking_ports_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::DockingPort>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_DockingPorts", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::ResourceHarvester>> SpaceCenter::Parts::resource_harvesters_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::ResourceHarvester>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_ResourceHarvesters", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Parachute>> SpaceCenter::Parts::parachutes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Parachute>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Parachutes", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::LaunchClamp>> SpaceCenter::Parts::launch_clamps_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::LaunchClamp>>(this->_client, this->_client->request("SpaceCenter", "Parts_get_LaunchClamps", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Parts::root_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Parts_get_Root", _args));
}

inline SpaceCenter::Propellant::Propellant(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Propellant", id) {}

inline float SpaceCenter::Propellant::ratio() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_Ratio", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Propellant::is_deprived() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_IsDeprived", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Propellant::current_amount() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_CurrentAmount", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Propellant::draw_stack_gauge() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_DrawStackGauge", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Propellant::ignore_for_thrust_curve() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_IgnoreForThrustCurve", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Propellant::total_resource_available() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_TotalResourceAvailable", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Propellant::total_resource_capacity() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_TotalResourceCapacity", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Propellant::ignore_for_isp() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_IgnoreForIsp", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Propellant::current_requirement() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_CurrentRequirement", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Propellant::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Propellant_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::Propellant::ratio_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_Ratio", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Propellant::is_deprived_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_IsDeprived", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Propellant::current_amount_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_CurrentAmount", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Propellant::draw_stack_gauge_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_DrawStackGauge", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Propellant::ignore_for_thrust_curve_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_IgnoreForThrustCurve", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Propellant::total_resource_available_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_TotalResourceAvailable", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Propellant::total_resource_capacity_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_TotalResourceCapacity", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Propellant::ignore_for_isp_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_IgnoreForIsp", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Propellant::current_requirement_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_CurrentRequirement", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Propellant::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Propellant_get_Name", _args));
}

inline SpaceCenter::RCS::RCS(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::RCS", id) {}

inline void SpaceCenter::RCS::set_roll_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_RollEnabled", _args);
}

inline float SpaceCenter::RCS::vacuum_specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_VacuumSpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::RCS::set_right_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_RightEnabled", _args);
}

inline bool SpaceCenter::RCS::has_fuel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_HasFuel", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::RCS::specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_SpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::roll_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_RollEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::yaw_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_YawEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::RCS::set_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_Enabled", _args);
}

inline void SpaceCenter::RCS::set_up_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_UpEnabled", _args);
}

inline float SpaceCenter::RCS::max_vacuum_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_MaxVacuumThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::right_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_RightEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::up_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_UpEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::RCS::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Thruster> SpaceCenter::RCS::thrusters() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_Thrusters", _args);
  std::vector<SpaceCenter::Thruster> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::RCS::propellants() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_Propellants", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::RCS::available_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_AvailableTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::map<std::string, float> SpaceCenter::RCS::propellant_ratios() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_PropellantRatios", _args);
  std::map<std::string, float> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::RCS::kerbin_sea_level_specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_KerbinSeaLevelSpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_Enabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::RCS::set_yaw_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_YawEnabled", _args);
}

inline void SpaceCenter::RCS::set_pitch_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_PitchEnabled", _args);
}

inline void SpaceCenter::RCS::set_forward_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "RCS_set_ForwardEnabled", _args);
}

inline float SpaceCenter::RCS::max_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_MaxThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::pitch_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_PitchEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::RCS::forward_enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "RCS_get_ForwardEnabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::RCS::vacuum_specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "RCS_get_VacuumSpecificImpulse", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::has_fuel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_HasFuel", _args));
}

inline ::krpc::Stream<float> SpaceCenter::RCS::specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "RCS_get_SpecificImpulse", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::roll_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_RollEnabled", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::yaw_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_YawEnabled", _args));
}

inline ::krpc::Stream<float> SpaceCenter::RCS::max_vacuum_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "RCS_get_MaxVacuumThrust", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::right_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_RightEnabled", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::up_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_UpEnabled", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::RCS::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "RCS_get_Part", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Thruster>> SpaceCenter::RCS::thrusters_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Thruster>>(this->_client, this->_client->request("SpaceCenter", "RCS_get_Thrusters", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_Active", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::RCS::propellants_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "RCS_get_Propellants", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::RCS::available_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "RCS_get_AvailableTorque", _args));
}

inline ::krpc::Stream<std::map<std::string, float>> SpaceCenter::RCS::propellant_ratios_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::map<std::string, float>>(this->_client, this->_client->request("SpaceCenter", "RCS_get_PropellantRatios", _args));
}

inline ::krpc::Stream<float> SpaceCenter::RCS::kerbin_sea_level_specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "RCS_get_KerbinSeaLevelSpecificImpulse", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_Enabled", _args));
}

inline ::krpc::Stream<float> SpaceCenter::RCS::max_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "RCS_get_MaxThrust", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::pitch_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_PitchEnabled", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::RCS::forward_enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "RCS_get_ForwardEnabled", _args));
}

inline SpaceCenter::Radiator::Radiator(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Radiator", id) {}

inline void SpaceCenter::Radiator::set_deployed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Radiator_set_Deployed", _args);
}

inline SpaceCenter::RadiatorState SpaceCenter::Radiator::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Radiator_get_State", _args);
  SpaceCenter::RadiatorState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Radiator::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Radiator_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Radiator::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Radiator_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Radiator::deployable() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Radiator_get_Deployable", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::RadiatorState> SpaceCenter::Radiator::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::RadiatorState>(this->_client, this->_client->request("SpaceCenter", "Radiator_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Radiator::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Radiator_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Radiator::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Radiator_get_Deployed", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Radiator::deployable_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Radiator_get_Deployable", _args));
}

inline SpaceCenter::ReactionWheel::ReactionWheel(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ReactionWheel", id) {}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::ReactionWheel::max_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ReactionWheel_get_MaxTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::ReactionWheel::set_active(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ReactionWheel_set_Active", _args);
}

inline bool SpaceCenter::ReactionWheel::broken() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ReactionWheel_get_Broken", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::ReactionWheel::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ReactionWheel_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ReactionWheel::active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ReactionWheel_get_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::ReactionWheel::available_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ReactionWheel_get_AvailableTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::ReactionWheel::max_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "ReactionWheel_get_MaxTorque", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ReactionWheel::broken_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ReactionWheel_get_Broken", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::ReactionWheel::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "ReactionWheel_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ReactionWheel::active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ReactionWheel_get_Active", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::ReactionWheel::available_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "ReactionWheel_get_AvailableTorque", _args));
}

inline SpaceCenter::ReferenceFrame::ReferenceFrame(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ReferenceFrame", id) {}

inline SpaceCenter::ReferenceFrame SpaceCenter::ReferenceFrame::create_hybrid(Client& _client, SpaceCenter::ReferenceFrame position, SpaceCenter::ReferenceFrame rotation = SpaceCenter::ReferenceFrame(), SpaceCenter::ReferenceFrame velocity = SpaceCenter::ReferenceFrame(), SpaceCenter::ReferenceFrame angular_velocity = SpaceCenter::ReferenceFrame()) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(velocity));
  _args.push_back(encoder::encode(angular_velocity));
  std::string _data = _client.invoke("SpaceCenter", "ReferenceFrame_CreateHybrid", _args);
    SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::ReferenceFrame::create_relative(Client& _client, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position = std::tuple<double, double, double>{0.0, 0.0, 0.0}, std::tuple<double, double, double, double> rotation = std::tuple<double, double, double, double>{0.0, 0.0, 0.0, 1.0}, std::tuple<double, double, double> velocity = std::tuple<double, double, double>{0.0, 0.0, 0.0}, std::tuple<double, double, double> angular_velocity = std::tuple<double, double, double>{0.0, 0.0, 0.0}) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(velocity));
  _args.push_back(encoder::encode(angular_velocity));
  std::string _data = _client.invoke("SpaceCenter", "ReferenceFrame_CreateRelative", _args);
    SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::ReferenceFrame::create_hybrid_stream(Client& _client, SpaceCenter::ReferenceFrame position, SpaceCenter::ReferenceFrame rotation = SpaceCenter::ReferenceFrame(), SpaceCenter::ReferenceFrame velocity = SpaceCenter::ReferenceFrame(), SpaceCenter::ReferenceFrame angular_velocity = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(velocity));
  _args.push_back(encoder::encode(angular_velocity));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(&_client, _client.request("SpaceCenter", "ReferenceFrame_CreateHybrid", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::ReferenceFrame::create_relative_stream(Client& _client, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position = std::tuple<double, double, double>{0.0, 0.0, 0.0}, std::tuple<double, double, double, double> rotation = std::tuple<double, double, double, double>{0.0, 0.0, 0.0, 1.0}, std::tuple<double, double, double> velocity = std::tuple<double, double, double>{0.0, 0.0, 0.0}, std::tuple<double, double, double> angular_velocity = std::tuple<double, double, double>{0.0, 0.0, 0.0}) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(velocity));
  _args.push_back(encoder::encode(angular_velocity));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(&_client, _client.request("SpaceCenter", "ReferenceFrame_CreateRelative", _args));
}

inline SpaceCenter::Resource::Resource(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Resource", id) {}

inline std::string SpaceCenter::Resource::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Resource::density() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_Density", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Resource::max() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_Max", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Resource::enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_Enabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Resource::amount() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_Amount", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Resource::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Resource::set_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Resource_set_Enabled", _args);
}

inline SpaceCenter::ResourceFlowMode SpaceCenter::Resource::flow_mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resource_get_FlowMode", _args);
  SpaceCenter::ResourceFlowMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::string> SpaceCenter::Resource::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Resource_get_Name", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Resource::density_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Resource_get_Density", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Resource::max_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Resource_get_Max", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Resource::enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Resource_get_Enabled", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Resource::amount_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Resource_get_Amount", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Resource::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Resource_get_Part", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceFlowMode> SpaceCenter::Resource::flow_mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ResourceFlowMode>(this->_client, this->_client->request("SpaceCenter", "Resource_get_FlowMode", _args));
}

inline SpaceCenter::ResourceConverter::ResourceConverter(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ResourceConverter", id) {}

inline bool SpaceCenter::ResourceConverter::active(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::ResourceConverter::inputs(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_Inputs", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::ResourceConverter::name(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::ResourceConverter::outputs(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_Outputs", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::ResourceConverter::start(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  this->_client->invoke("SpaceCenter", "ResourceConverter_Start", _args);
}

inline SpaceCenter::ResourceConverterState SpaceCenter::ResourceConverter::state(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_State", _args);
  SpaceCenter::ResourceConverterState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::ResourceConverter::status_info(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_StatusInfo", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::ResourceConverter::stop(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  this->_client->invoke("SpaceCenter", "ResourceConverter_Stop", _args);
}

inline google::protobuf::int32 SpaceCenter::ResourceConverter::count() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_get_Count", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::ResourceConverter::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceConverter_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> SpaceCenter::ResourceConverter::active_stream(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_Active", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::ResourceConverter::inputs_stream(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_Inputs", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::ResourceConverter::name_stream(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_Name", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::ResourceConverter::outputs_stream(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_Outputs", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceConverterState> SpaceCenter::ResourceConverter::state_stream(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<SpaceCenter::ResourceConverterState>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_State", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::ResourceConverter::status_info_stream(google::protobuf::int32 index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_StatusInfo", _args));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::ResourceConverter::count_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_get_Count", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::ResourceConverter::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "ResourceConverter_get_Part", _args));
}

inline SpaceCenter::ResourceHarvester::ResourceHarvester(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ResourceHarvester", id) {}

inline void SpaceCenter::ResourceHarvester::set_deployed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ResourceHarvester_set_Deployed", _args);
}

inline float SpaceCenter::ResourceHarvester::extraction_rate() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_ExtractionRate", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ResourceHarvester::thermal_efficiency() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_ThermalEfficiency", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::ResourceHarvester::set_active(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "ResourceHarvester_set_Active", _args);
}

inline float SpaceCenter::ResourceHarvester::optimum_core_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_OptimumCoreTemperature", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ResourceHarvester::core_temperature() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_CoreTemperature", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ResourceHarvesterState SpaceCenter::ResourceHarvester::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_State", _args);
  SpaceCenter::ResourceHarvesterState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::ResourceHarvester::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ResourceHarvester::active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ResourceHarvester::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceHarvester_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::ResourceHarvester::extraction_rate_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_ExtractionRate", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ResourceHarvester::thermal_efficiency_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_ThermalEfficiency", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ResourceHarvester::optimum_core_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_OptimumCoreTemperature", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ResourceHarvester::core_temperature_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_CoreTemperature", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceHarvesterState> SpaceCenter::ResourceHarvester::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ResourceHarvesterState>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::ResourceHarvester::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ResourceHarvester::active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_Active", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ResourceHarvester::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ResourceHarvester_get_Deployed", _args));
}

inline SpaceCenter::ResourceTransfer::ResourceTransfer(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ResourceTransfer", id) {}

inline float SpaceCenter::ResourceTransfer::amount() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceTransfer_get_Amount", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ResourceTransfer::complete() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ResourceTransfer_get_Complete", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ResourceTransfer SpaceCenter::ResourceTransfer::start(Client& _client, SpaceCenter::Part from_part, SpaceCenter::Part to_part, std::string resource, float max_amount) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(from_part));
  _args.push_back(encoder::encode(to_part));
  _args.push_back(encoder::encode(resource));
  _args.push_back(encoder::encode(max_amount));
  std::string _data = _client.invoke("SpaceCenter", "ResourceTransfer_Start", _args);
    SpaceCenter::ResourceTransfer _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::ResourceTransfer::amount_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ResourceTransfer_get_Amount", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ResourceTransfer::complete_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ResourceTransfer_get_Complete", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceTransfer> SpaceCenter::ResourceTransfer::start_stream(Client& _client, SpaceCenter::Part from_part, SpaceCenter::Part to_part, std::string resource, float max_amount) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(from_part));
  _args.push_back(encoder::encode(to_part));
  _args.push_back(encoder::encode(resource));
  _args.push_back(encoder::encode(max_amount));
  return ::krpc::Stream<SpaceCenter::ResourceTransfer>(&_client, _client.request("SpaceCenter", "ResourceTransfer_Start", _args));
}

inline SpaceCenter::Resources::Resources(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Resources", id) {}

inline float SpaceCenter::Resources::amount(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_Amount", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Resources::has_resource(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_HasResource", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Resources::max(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_Max", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Resource> SpaceCenter::Resources::with_resource(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_WithResource", _args);
  std::vector<SpaceCenter::Resource> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Resources::set_enabled(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Resources_set_Enabled", _args);
}

inline std::vector<SpaceCenter::Resource> SpaceCenter::Resources::all() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_get_All", _args);
  std::vector<SpaceCenter::Resource> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Resources::enabled() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_get_Enabled", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::Resources::names() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Resources_get_Names", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Resources::density(Client& _client, std::string name) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  std::string _data = _client.invoke("SpaceCenter", "Resources_Density", _args);
    float _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline SpaceCenter::ResourceFlowMode SpaceCenter::Resources::flow_mode(Client& _client, std::string name) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  std::string _data = _client.invoke("SpaceCenter", "Resources_FlowMode", _args);
    SpaceCenter::ResourceFlowMode _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::Resources::amount_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Resources_Amount", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Resources::has_resource_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Resources_HasResource", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Resources::max_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Resources_Max", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Resource>> SpaceCenter::Resources::with_resource_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<std::vector<SpaceCenter::Resource>>(this->_client, this->_client->request("SpaceCenter", "Resources_WithResource", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Resource>> SpaceCenter::Resources::all_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Resource>>(this->_client, this->_client->request("SpaceCenter", "Resources_get_All", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Resources::enabled_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Resources_get_Enabled", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::Resources::names_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "Resources_get_Names", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Resources::density_stream(Client& _client, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<float>(&_client, _client.request("SpaceCenter", "Resources_Density", _args));
}

inline ::krpc::Stream<SpaceCenter::ResourceFlowMode> SpaceCenter::Resources::flow_mode_stream(Client& _client, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<SpaceCenter::ResourceFlowMode>(&_client, _client.request("SpaceCenter", "Resources_FlowMode", _args));
}

inline SpaceCenter::ScienceData::ScienceData(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ScienceData", id) {}

inline float SpaceCenter::ScienceData::data_amount() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceData_get_DataAmount", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ScienceData::science_value() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceData_get_ScienceValue", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ScienceData::transmit_value() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceData_get_TransmitValue", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::ScienceData::data_amount_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceData_get_DataAmount", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ScienceData::science_value_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceData_get_ScienceValue", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ScienceData::transmit_value_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceData_get_TransmitValue", _args));
}

inline SpaceCenter::ScienceSubject::ScienceSubject(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::ScienceSubject", id) {}

inline float SpaceCenter::ScienceSubject::subject_value() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_SubjectValue", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ScienceSubject::science_cap() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_ScienceCap", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::ScienceSubject::title() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_Title", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ScienceSubject::science() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_Science", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ScienceSubject::scientific_value() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_ScientificValue", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::ScienceSubject::data_scale() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_DataScale", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::ScienceSubject::is_complete() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "ScienceSubject_get_IsComplete", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::ScienceSubject::subject_value_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_SubjectValue", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ScienceSubject::science_cap_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_ScienceCap", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::ScienceSubject::title_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_Title", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ScienceSubject::science_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_Science", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ScienceSubject::scientific_value_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_ScientificValue", _args));
}

inline ::krpc::Stream<float> SpaceCenter::ScienceSubject::data_scale_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_DataScale", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::ScienceSubject::is_complete_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "ScienceSubject_get_IsComplete", _args));
}

inline SpaceCenter::Sensor::Sensor(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Sensor", id) {}

inline bool SpaceCenter::Sensor::active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Sensor_get_Active", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Sensor::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Sensor_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Sensor::value() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Sensor_get_Value", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Sensor::set_active(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Sensor_set_Active", _args);
}

inline ::krpc::Stream<bool> SpaceCenter::Sensor::active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Sensor_get_Active", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Sensor::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Sensor_get_Part", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Sensor::value_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Sensor_get_Value", _args));
}

inline SpaceCenter::SolarPanel::SolarPanel(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::SolarPanel", id) {}

inline float SpaceCenter::SolarPanel::energy_flow() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "SolarPanel_get_EnergyFlow", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::SolarPanel::set_deployed(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "SolarPanel_set_Deployed", _args);
}

inline SpaceCenter::SolarPanelState SpaceCenter::SolarPanel::state() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "SolarPanel_get_State", _args);
  SpaceCenter::SolarPanelState _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::SolarPanel::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "SolarPanel_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::SolarPanel::sun_exposure() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "SolarPanel_get_SunExposure", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::SolarPanel::deployed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "SolarPanel_get_Deployed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> SpaceCenter::SolarPanel::energy_flow_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "SolarPanel_get_EnergyFlow", _args));
}

inline ::krpc::Stream<SpaceCenter::SolarPanelState> SpaceCenter::SolarPanel::state_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::SolarPanelState>(this->_client, this->_client->request("SpaceCenter", "SolarPanel_get_State", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::SolarPanel::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "SolarPanel_get_Part", _args));
}

inline ::krpc::Stream<float> SpaceCenter::SolarPanel::sun_exposure_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "SolarPanel_get_SunExposure", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::SolarPanel::deployed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "SolarPanel_get_Deployed", _args));
}

inline SpaceCenter::Thruster::Thruster(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Thruster", id) {}

inline std::tuple<double, double, double> SpaceCenter::Thruster::gimbal_position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_GimbalPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Thruster::initial_thrust_direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_InitialThrustDirection", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Thruster::initial_thrust_position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_InitialThrustPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Thruster::thrust_direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_ThrustDirection", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Thruster::thrust_position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_ThrustPosition", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Thruster::thrust_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_get_ThrustReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Thruster::gimbal_angle() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_get_GimbalAngle", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part SpaceCenter::Thruster::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Thruster::gimballed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Thruster_get_Gimballed", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Thruster::gimbal_position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Thruster_GimbalPosition", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Thruster::initial_thrust_direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Thruster_InitialThrustDirection", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Thruster::initial_thrust_position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Thruster_InitialThrustPosition", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Thruster::thrust_direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Thruster_ThrustDirection", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Thruster::thrust_position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Thruster_ThrustPosition", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Thruster::thrust_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Thruster_get_ThrustReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Thruster::gimbal_angle_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Thruster_get_GimbalAngle", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> SpaceCenter::Thruster::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->request("SpaceCenter", "Thruster_get_Part", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Thruster::gimballed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Thruster_get_Gimballed", _args));
}

inline SpaceCenter::Vessel::Vessel(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Vessel", id) {}

inline std::tuple<double, double, double> SpaceCenter::Vessel::angular_velocity(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_AngularVelocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::bounding_box(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_BoundingBox", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Vessel::direction(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_Direction", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Flight SpaceCenter::Vessel::flight(SpaceCenter::ReferenceFrame reference_frame = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_Flight", _args);
  SpaceCenter::Flight _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Vessel::position(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Vessel::recover() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Vessel_Recover", _args);
}

inline SpaceCenter::Resources SpaceCenter::Vessel::resources_in_decouple_stage(google::protobuf::int32 stage, bool cumulative = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(stage));
  _args.push_back(encoder::encode(cumulative));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_ResourcesInDecoupleStage", _args);
  SpaceCenter::Resources _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double, double> SpaceCenter::Vessel::rotation(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Vessel::velocity(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_Velocity", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Control SpaceCenter::Vessel::control() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Control", _args);
  SpaceCenter::Control _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::available_rcs_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableRCSTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::available_reaction_wheel_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableReactionWheelTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_SpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::available_other_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableOtherTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<double> SpaceCenter::Vessel::inertia_tensor() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_InertiaTensor", _args);
  std::vector<double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Vessel::biome() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Biome", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Vessel::surface_velocity_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_SurfaceVelocityReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::available_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Parts SpaceCenter::Vessel::parts() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Parts", _args);
  SpaceCenter::Parts _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Vessel::orbital_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_OrbitalReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::AutoPilot SpaceCenter::Vessel::auto_pilot() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AutoPilot", _args);
  SpaceCenter::AutoPilot _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Mass", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::VesselType SpaceCenter::Vessel::type() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Type", _args);
  SpaceCenter::VesselType _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Resources SpaceCenter::Vessel::resources() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Resources", _args);
  SpaceCenter::Resources _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Vessel::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double, double> SpaceCenter::Vessel::moment_of_inertia() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_MomentOfInertia", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::max_vacuum_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_MaxVacuumThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Vessel::set_type(SpaceCenter::VesselType value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Vessel_set_Type", _args);
}

inline double SpaceCenter::Vessel::met() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_MET", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::VesselSituation SpaceCenter::Vessel::situation() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Situation", _args);
  SpaceCenter::VesselSituation _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Thrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::available_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Vessel::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Vessel_set_Name", _args);
}

inline std::string SpaceCenter::Vessel::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::kerbin_sea_level_specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_KerbinSeaLevelSpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Orbit SpaceCenter::Vessel::orbit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Orbit", _args);
  SpaceCenter::Orbit _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::available_engine_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableEngineTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::ReferenceFrame SpaceCenter::Vessel::surface_reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_SurfaceReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::vacuum_specific_impulse() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_VacuumSpecificImpulse", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > SpaceCenter::Vessel::available_control_surface_torque() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_AvailableControlSurfaceTorque", _args);
  std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::max_thrust() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_MaxThrust", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float SpaceCenter::Vessel::dry_mass() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_DryMass", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Vessel::recoverable() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Vessel_get_Recoverable", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Vessel::angular_velocity_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_AngularVelocity", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::bounding_box_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_BoundingBox", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Vessel::direction_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_Direction", _args));
}

inline ::krpc::Stream<SpaceCenter::Flight> SpaceCenter::Vessel::flight_stream(SpaceCenter::ReferenceFrame reference_frame = SpaceCenter::ReferenceFrame()) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<SpaceCenter::Flight>(this->_client, this->_client->request("SpaceCenter", "Vessel_Flight", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Vessel::position_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_Position", _args));
}

inline ::krpc::Stream<SpaceCenter::Resources> SpaceCenter::Vessel::resources_in_decouple_stage_stream(google::protobuf::int32 stage, bool cumulative = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(stage));
  _args.push_back(encoder::encode(cumulative));
  return ::krpc::Stream<SpaceCenter::Resources>(this->_client, this->_client->request("SpaceCenter", "Vessel_ResourcesInDecoupleStage", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> SpaceCenter::Vessel::rotation_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_Rotation", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Vessel::velocity_stream(SpaceCenter::ReferenceFrame reference_frame) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(reference_frame));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_Velocity", _args));
}

inline ::krpc::Stream<SpaceCenter::Control> SpaceCenter::Vessel::control_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Control>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Control", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::available_rcs_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableRCSTorque", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::available_reaction_wheel_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableReactionWheelTorque", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_SpecificImpulse", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::available_other_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableOtherTorque", _args));
}

inline ::krpc::Stream<std::vector<double>> SpaceCenter::Vessel::inertia_tensor_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_InertiaTensor", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Vessel::biome_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Biome", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Vessel::surface_velocity_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_SurfaceVelocityReferenceFrame", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::available_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableThrust", _args));
}

inline ::krpc::Stream<SpaceCenter::Parts> SpaceCenter::Vessel::parts_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Parts>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Parts", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Vessel::orbital_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_OrbitalReferenceFrame", _args));
}

inline ::krpc::Stream<SpaceCenter::AutoPilot> SpaceCenter::Vessel::auto_pilot_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::AutoPilot>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AutoPilot", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Mass", _args));
}

inline ::krpc::Stream<SpaceCenter::VesselType> SpaceCenter::Vessel::type_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::VesselType>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Type", _args));
}

inline ::krpc::Stream<SpaceCenter::Resources> SpaceCenter::Vessel::resources_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Resources>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Resources", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Vessel::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> SpaceCenter::Vessel::moment_of_inertia_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_MomentOfInertia", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::max_vacuum_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_MaxVacuumThrust", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Vessel::met_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_MET", _args));
}

inline ::krpc::Stream<SpaceCenter::VesselSituation> SpaceCenter::Vessel::situation_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::VesselSituation>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Situation", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Thrust", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::available_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableTorque", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Vessel::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Name", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::kerbin_sea_level_specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_KerbinSeaLevelSpecificImpulse", _args));
}

inline ::krpc::Stream<SpaceCenter::Orbit> SpaceCenter::Vessel::orbit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Orbit>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Orbit", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::available_engine_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableEngineTorque", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> SpaceCenter::Vessel::surface_reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_SurfaceReferenceFrame", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::vacuum_specific_impulse_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_VacuumSpecificImpulse", _args));
}

inline ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >> SpaceCenter::Vessel::available_control_surface_torque_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double> >>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_AvailableControlSurfaceTorque", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::max_thrust_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_MaxThrust", _args));
}

inline ::krpc::Stream<float> SpaceCenter::Vessel::dry_mass_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_DryMass", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Vessel::recoverable_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Vessel_get_Recoverable", _args));
}

inline SpaceCenter::Waypoint::Waypoint(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::Waypoint", id) {}

inline void SpaceCenter::Waypoint::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("SpaceCenter", "Waypoint_Remove", _args);
}

inline void SpaceCenter::Waypoint::set_body(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_Body", _args);
}

inline google::protobuf::int32 SpaceCenter::Waypoint::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Color", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Waypoint::set_icon(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_Icon", _args);
}

inline bool SpaceCenter::Waypoint::near_surface() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_NearSurface", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Waypoint::set_longitude(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_Longitude", _args);
}

inline google::protobuf::int32 SpaceCenter::Waypoint::index() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Index", _args);
  google::protobuf::int32 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Waypoint::mean_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_MeanAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Waypoint::grounded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Grounded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool SpaceCenter::Waypoint::has_contract() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_HasContract", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Waypoint::surface_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_SurfaceAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Waypoint::latitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Latitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string SpaceCenter::Waypoint::icon() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Icon", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Waypoint::bedrock_altitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_BedrockAltitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::CelestialBody SpaceCenter::Waypoint::body() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Body", _args);
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Waypoint::set_surface_altitude(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_SurfaceAltitude", _args);
}

inline bool SpaceCenter::Waypoint::clustered() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Clustered", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline google::protobuf::int64 SpaceCenter::Waypoint::contract_id() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_ContractId", _args);
  google::protobuf::int64 _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Waypoint::set_bedrock_altitude(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_BedrockAltitude", _args);
}

inline void SpaceCenter::Waypoint::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_Name", _args);
}

inline std::string SpaceCenter::Waypoint::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double SpaceCenter::Waypoint::longitude() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "Waypoint_get_Longitude", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void SpaceCenter::Waypoint::set_latitude(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_Latitude", _args);
}

inline void SpaceCenter::Waypoint::set_mean_altitude(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_MeanAltitude", _args);
}

inline void SpaceCenter::Waypoint::set_color(google::protobuf::int32 value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("SpaceCenter", "Waypoint_set_Color", _args);
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::Waypoint::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Color", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Waypoint::near_surface_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_NearSurface", _args));
}

inline ::krpc::Stream<google::protobuf::int32> SpaceCenter::Waypoint::index_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int32>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Index", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Waypoint::mean_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_MeanAltitude", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Waypoint::grounded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Grounded", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Waypoint::has_contract_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_HasContract", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Waypoint::surface_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_SurfaceAltitude", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Waypoint::latitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Latitude", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Waypoint::icon_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Icon", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Waypoint::bedrock_altitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_BedrockAltitude", _args));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> SpaceCenter::Waypoint::body_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Body", _args));
}

inline ::krpc::Stream<bool> SpaceCenter::Waypoint::clustered_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Clustered", _args));
}

inline ::krpc::Stream<google::protobuf::int64> SpaceCenter::Waypoint::contract_id_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<google::protobuf::int64>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_ContractId", _args));
}

inline ::krpc::Stream<std::string> SpaceCenter::Waypoint::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Name", _args));
}

inline ::krpc::Stream<double> SpaceCenter::Waypoint::longitude_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->request("SpaceCenter", "Waypoint_get_Longitude", _args));
}

inline SpaceCenter::WaypointManager::WaypointManager(Client* client, google::protobuf::uint64 id):
  Object(client, "SpaceCenter::WaypointManager", id) {}

inline SpaceCenter::Waypoint SpaceCenter::WaypointManager::add_waypoint(double latitude, double longitude, SpaceCenter::CelestialBody body, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(body));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("SpaceCenter", "WaypointManager_AddWaypoint", _args);
  SpaceCenter::Waypoint _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::map<std::string, google::protobuf::int32> SpaceCenter::WaypointManager::colors() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "WaypointManager_get_Colors", _args);
  std::map<std::string, google::protobuf::int32> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<SpaceCenter::Waypoint> SpaceCenter::WaypointManager::waypoints() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "WaypointManager_get_Waypoints", _args);
  std::vector<SpaceCenter::Waypoint> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<std::string> SpaceCenter::WaypointManager::icons() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("SpaceCenter", "WaypointManager_get_Icons", _args);
  std::vector<std::string> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<SpaceCenter::Waypoint> SpaceCenter::WaypointManager::add_waypoint_stream(double latitude, double longitude, SpaceCenter::CelestialBody body, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(latitude));
  _args.push_back(encoder::encode(longitude));
  _args.push_back(encoder::encode(body));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<SpaceCenter::Waypoint>(this->_client, this->_client->request("SpaceCenter", "WaypointManager_AddWaypoint", _args));
}

inline ::krpc::Stream<std::map<std::string, google::protobuf::int32>> SpaceCenter::WaypointManager::colors_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::map<std::string, google::protobuf::int32>>(this->_client, this->_client->request("SpaceCenter", "WaypointManager_get_Colors", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Waypoint>> SpaceCenter::WaypointManager::waypoints_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Waypoint>>(this->_client, this->_client->request("SpaceCenter", "WaypointManager_get_Waypoints", _args));
}

inline ::krpc::Stream<std::vector<std::string>> SpaceCenter::WaypointManager::icons_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::string>>(this->_client, this->_client->request("SpaceCenter", "WaypointManager_get_Icons", _args));
}
}  // namespace services

}  // namespace krpc
