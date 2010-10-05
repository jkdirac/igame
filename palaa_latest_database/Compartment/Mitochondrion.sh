file = [Mitochondrion.xml]

MoDeL
{
	compartment id = [Mitochondrion], name = [Mitochondrion], spatialDimensions = [3], size = [1E-18], units = [litre]
	{
		listOfInnerCompartmentPermitted
		{
			compartmentReference:[Mitochondrion];
		}
	}
}

