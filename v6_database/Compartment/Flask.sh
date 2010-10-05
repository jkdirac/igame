file = [Flask.xml]

MoDeL
{
	compartment id = [Flask], name = [Flask], spatialDimensions = [3], size = [0.25], units = [litre]
	{
		listOfInnerCompartmentPermitted
		{
			compartmentReference:[E_coli];
		}
	}
}

