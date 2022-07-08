modded class FireplaceBase
{
	const float PARAM_FULL_HEAT_RADIUS = 2.5;
	const float PARAM_HEAT_RADIUS = 5.0;
	const float PARAM_HEAT_THROUGH_AIR_COEF	= 0.035;
	const float PARAM_HEAT_THROUGH_AIR_COEF_BOOST = 0.1;
	const float PARAM_HEAT_ITEM_COEF = 6.0;
	const float PARAM_HEAT_ITEM_MAX_TEMP = 40.0;
	
	override protected void TransferHeatToNearPlayers()
	{
		super.TransferHeatToNearPlayers();
		
		array<Object> nearest_objects = new array<Object>;
		GetGame().GetObjectsAtPosition ( GetPosition(), PARAM_FULL_HEAT_RADIUS, nearest_objects, NULL ); 
		
		PlayerBase player;
		ItemBase item;
		foreach (Object nearest_object : nearest_objects)
		{
			if (nearest_object != this && nearest_object.GetParent() == null)
			{
				if (PlayerBase.CastTo(player, nearest_object))
				{
					if (player.GetStatHeatComfort().Get() < 0)
					{
						player.AddToEnvironmentTemperature( Math.Min( GetTemperature() * PARAM_HEAT_THROUGH_AIR_COEF_BOOST, 60 ) );
					}
				}
				else if (ItemBase.CastTo(item, nearest_object))
				{
					if (item.IsTemperatureVisible() && item.GetTemperature() < GetTemperature() && item.GetTemperature() < PARAM_HEAT_ITEM_MAX_TEMP)
					{
						item.AddTemperature( PARAM_HEAT_ITEM_COEF );
					}
				}
			}
		}
	}
	
	bool IsTemperatureVisible()
	{
		return GetTemperature() > PARAM_MIN_FIRE_TEMPERATURE;
	}
};